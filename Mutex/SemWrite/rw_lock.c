#include<semaphore.h>
#include <sys/signal.h>

typedef struct
{
    sem_t mutex;

    sem_t reader_count_mutex;
    uint reader_count;
} sem_rwlock_t;

int sem_rwlock_init(sem_rwlock_t* sem_rw_lock)
{
    sem_rw_lock->reader_count = 0;
    if (sem_init(&sem_rw_lock->mutex, 0, 1) != 0)return -1;
    if (sem_init(&sem_rw_lock->reader_count_mutex, 0, 1) != 0)return -1;
    return 0;
}

int sem_rwlock_rdlock(sem_rwlock_t* sem_rw_lock)
{
    struct sigaction
    sem_wait(&sem_rw_lock->reader_count_mutex);
    sem_rw_lock->reader_count++;
    if (sem_rw_lock->reader_count == 1)
    {
        sem_wait(&sem_rw_lock->mutex);
    }
    sem_post(&sem_rw_lock->reader_count_mutex);
    return 0;
}

int sem_rwlock_rdunlock(sem_rwlock_t* sem_rw_lock)
{
    sem_wait(&sem_rw_lock->reader_count_mutex);
    sem_rw_lock->reader_count--;
    if (sem_rw_lock->reader_count == 0)
    {
        sem_post(&sem_rw_lock->mutex);
    }
    sem_post(&sem_rw_lock->reader_count_mutex);
    return 0;
}


int sem_rwlock_wrlock(sem_rwlock_t* sem_rw_lock)
{
    return sem_wait(&sem_rw_lock->mutex);
}

int sem_rwlock_wrunlock(sem_rwlock_t* sem_rw_lock)
{
    return sem_post(&sem_rw_lock->mutex);
}

int sem_rwlock_destroy(sem_rwlock_t* sem_rw_lock)
{
    if (sem_destroy(&sem_rw_lock->mutex) != 0)return -1;
    if (sem_destroy(&sem_rw_lock->reader_count_mutex) != 0)return -1;
    return 0;
}
