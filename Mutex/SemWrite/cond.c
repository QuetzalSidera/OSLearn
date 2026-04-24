#include <pthread.h>
#include<semaphore.h>

typedef struct
{
    sem_t cond;
    int waiters;
    //waiters的锁
    sem_t mutex;
} sem_cond_t;

int sem_cond_init(sem_cond_t* sem_cond)
{
    //mutex初始化为1 cond初始化为0
    if (sem_init(&sem_cond->mutex, 0, 1) != 0)return -1;
    if (sem_init(&sem_cond->cond, 0, 0) != 0)return -1;
    return 0;
}

int sem_cond_wait(sem_cond_t* sem_cond)
{
    sem_wait(&sem_cond->mutex);
    sem_cond->waiters++;
    sem_post(&sem_cond->mutex);
    //waiters++与sem_wait在此处存在时差
    //且sem_wait(&sem_cond->cond);不能移到mutex内部（死锁）
    sem_wait(&sem_cond->cond);
    return 0;
}

int sem_cond_signal(sem_cond_t* sem_cond)
{
    sem_wait(&sem_cond->mutex);
    if (sem_cond->waiters > 0)
    {
        sem_cond->waiters--;
        sem_post(&sem_cond->cond);
    }
    sem_post(&sem_cond->mutex);
    return 0;
}


int sem_cond_broadcast(sem_cond_t* sem_cond)
{
    sem_wait(&sem_cond->mutex);
    for (int i = 0; i < sem_cond->waiters; i++)
    {
        sem_post(&sem_cond->cond);
    }
    sem_cond->waiters = 0;
    sem_post(&sem_cond->mutex);
    return 0;
}


int sem_cond_destroy(sem_cond_t* sem_cond)
{
    if (sem_destroy(&sem_cond->mutex) != 0)return -1;
    if (sem_destroy(&sem_cond->cond) != 0)return -1;
    return 0;
}
