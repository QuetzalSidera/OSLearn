#include <pthread.h>

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    unsigned int value;
} mutex_cond_sem_t;

int mutex_cond_sem_init(mutex_cond_sem_t* sem, unsigned int value)
{
    sem->value = value;
    if (pthread_mutex_init(&sem->mutex, NULL) != 0) return -1;
    if (pthread_cond_init(&sem->cond, NULL) != 0) return -1;
    return 0;
}

int mutex_cond_sem_wait(mutex_cond_sem_t* sem)
{
    pthread_mutex_lock(&sem->mutex);
    while (sem->value == 0)
    {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--;
    pthread_mutex_unlock(&sem->mutex);
    return 0;
}

int mutex_cond_sem_post(mutex_cond_sem_t* sem)
{
    pthread_mutex_lock(&sem->mutex);
    sem->value++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);
    return 0;
}

int mutex_cond_sem_destroy(mutex_cond_sem_t* sem)
{
    if (pthread_mutex_destroy(&sem->mutex) != 0) return -1;
    if (pthread_cond_destroy(&sem->cond) != 0) return -1;
    return 0;
}
