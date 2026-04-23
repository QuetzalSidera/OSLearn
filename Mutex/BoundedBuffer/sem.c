#include <semaphore.h>
#define BUFFER_SIZE 100
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10
//共享资源
int buffer[BUFFER_SIZE];
//consume与produce指针
int consumeIndex;
int produceIndex;

sem_t sem;

void init()
{
    sem_init(&sem, 0, 1);
}
