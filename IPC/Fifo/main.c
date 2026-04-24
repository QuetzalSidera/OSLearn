#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    const char* name = "/Fifo";

    if (fork() == 0)
    {
        const int fifo = mkfifo(name, 0666);
    }
}

