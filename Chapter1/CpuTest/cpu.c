#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: cpu ‹string>\n");
        exit(1);
    }
    char* str = argv[1];
    while (1)
    {
        atexit()
        // Spin(1);
        int fd1 = open("in.txt", O_RDONLY); //fd1 == 3;
        close(STDOUT_FILENO);
        int fd2 = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        printf("%s\n", str);
    }
    return 0;
}
