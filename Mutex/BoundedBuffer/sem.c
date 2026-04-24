#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void init();
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

sem_t empty; // 空槽数量
sem_t full; // 已用槽数量
sem_t mutex; // 互斥（可以是二值信号量）
void init()
{
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    srand(time(NULL)); // 只在程序开始调用一次
}

void* consume(void* arg)
{
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        printf("\n");
        printf("consumeIndex: %d\n", consumeIndex);
        printf("consume: %d\n", buffer[consumeIndex]);
        printf("\n");
        consumeIndex = (consumeIndex + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
        //12us
        usleep(12);
    }
}

void* produce(void* arg)
{
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("\n");
        printf("produceIndex: %d\n", produceIndex);
        printf("produce: %d\n", buffer[produceIndex]);
        printf("\n");
        produceIndex = (produceIndex + 1) % BUFFER_SIZE;
        buffer[produceIndex] = data();
        sem_post(&mutex);
        sem_post(&full);


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
