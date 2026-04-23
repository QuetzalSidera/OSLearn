#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t rc = fork();

    if (rc < 0) {
        perror("fork");
        exit(1);
    }

    if (rc == 0) {
        execlp("ls", "ls", "-l", NULL);

        // 只有 exec 失败时，才会走到这里
        perror("execlp");
        exit(1);
    } else {
        waitpid(rc, NULL, 0);
        printf("parent: child finished\n");
    }

    return 0;
}