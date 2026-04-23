#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_arg
{
    int upper;
};

//计算从1->upper的累加值
void* runner(void* arg)
{
    int upper = ((struct thread_arg*)arg)->upper;
    long sum = 0;

    for (int i = 1; i <= upper; i++)
    {
        sum += i;
    }
    return (void*)sum;
}

int main(const int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <positive-int>\n", argv[0]);
        return 1;
    }

    pthread_t tid;
    struct thread_arg arg;


    arg.upper = atoi(argv[1]);
    void* sum;
    //创建线程
    pthread_create(&tid, NULL, runner, &arg);
    //等待线程结束
    pthread_join(tid, &sum);
    //获取计算结果
    printf("sum = %ld\n", (long)sum);
    return 0;
}
