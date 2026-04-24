#include<semaphore.h>

typedef struct
{
    sem_t mutex;
} sem_cond_tsem_mutex_t;

int sem_mutex_init(sem_mutex_t* sem_mutex)
{
    return sem_init(&sem_mutex->mutex, 0, 1);
}

int sem_mutex_lock(sem_mutex_t* sem_mutex)
{
    return sem_wait(&sem_mutex->mutex);
}

int sem_mutex_unlock(sem_mutex_t* sem_mutex)
{
    return sem_post(&sem_mutex->mutex);
}

int sem_mutex_destroy(sem_msem_cond_tutex_t* sem_mutex)
{
    return sem_destroy(&sem_mutex->mutex);
}
