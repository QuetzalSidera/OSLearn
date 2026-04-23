#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int init();
void* consume(void* arg);
void* produce(void* arg);
int data();

#define BUFFER_SIZE 100
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10
//共享资源
int buffer[BUFFER_SIZE];
//consume与produce指针
int consumeIndex;
int produceIndex;
//条件变量
pthread_cond_t empty;
pthread_cond_t full;
//锁
pthread_mutex_t mutex;

int init()
{
    consumeIndex = 0;
    produceIndex = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);

    srand(time(NULL)); // 只在程序开始调用一次
    return 0;
}

void* consume(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (consumeIndex == produceIndex)
        {
            pthread_cond_wait(&full, &mutex);
        }
        printf("\n");
        printf("consumeIndex: %d\n", consumeIndex);
        printf("consume: %d\n", buffer[consumeIndex]);
        printf("\n");
        consumeIndex = (consumeIndex + 1) % BUFFER_SIZE;
        pthread_cond_broadcast(&empty);
        pthread_mutex_unlock(&mutex);
        //10us
        usleep(10);
    }
}

void* produce(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while ((produceIndex + 1) % BUFFER_SIZE == consumeIndex)
        {
            pthread_cond_wait(&empty, &mutex);
        }
        produceIndex = (produceIndex + 1) % BUFFER_SIZE;
        buffer[produceIndex] = data();

        printf("\n");
        printf("produceIndex: %d\n", produceIndex);
        printf("produce: %d\n", buffer[produceIndex]);
        printf("\n");

        pthread_cond_broadcast(&full);
        pthread_mutex_unlock(&mutex);

        //10us
        usleep(10);
    }
}

int data()
{
    return rand() % 90 + 10; // 生成 10~99 的随机数
}

int main(void)
{
    init();
    pthread_t consumer[NUM_CONSUMERS];
    pthread_t producer[NUM_PRODUCERS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumer[i], &attr, consume,NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_create(&producer[i], &attr, produce, NULL);
    }
    pthread_exit(NULL);
}
