#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define READER_COUNT 10
#define WRITER_COUNT 10

#define QUEUE_SIZE 8

typedef struct queue_t
{
    int data[QUEUE_SIZE];
    //头尾指针
    int head;
    int tail;

    int count;
    //锁与条件变量
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} queue_t;

void queue_push(queue_t* q, int value)
{
    pthread_mutex_lock(&q->mutex);
    while (q->count == QUEUE_SIZE)
    {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
    q->count++;

    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mutex);
}

int queue_pop(queue_t* q)
{
    pthread_mutex_lock(&q->mutex);
    while (q->count == 0)
    {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    int value = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;

    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    return value;
}


int data()
{
    return rand() % 90 + 10; // 生成 10~99 的随机数
}


void* readWorker(void* arg)
{
    queue_t* queue = (queue_t*)arg;
    while (1)
    {
        queue->pop(queue);
        usleep(120);
    }
}

void* writeWorker(void* arg)
{
    queue_t* queue = (queue_t*)arg;
    while (1)
    {
        queue->push(queue, data());
        usleep(100);
    }
}


int main(int argc, char* argv[])
{
    srand(time(NULL));
    const queue_t* queue = init();
    pthread_t reader[READER_COUNT];
    pthread_t writer[WRITER_COUNT];
    for (int i = 0; i < READER_COUNT; i++)
    {
        pthread_create(&reader[i], NULL, readWorker, (void*)queue);
    }
    for (int i = 0; i < WRITER_COUNT; i++)
    {
        pthread_create(&writer[i], NULL, writeWorker, (void*)queue);
    }
    pthread_exit(NULL);
}

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
static pthread_mutex_t chopstick[5];

void philosopher(int i)
{
    int left = i;
    int right = (i + 1) % 5;
    int first = MIN(left, right);
    int second = MAX(left, right);

    pthread_mutex_lock(&chopstick[first]);
    pthread_mutex_lock(&chopstick[second]);

    /* eat */

    pthread_mutex_unlock(&chopstick[second]);
    pthread_mutex_unlock(&chopstick[first]);
}
