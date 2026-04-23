#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <_string.h>

int main(int argc, char* argv[])
{
    if (fork() == 0)
    {
        WNOHANG
        printf("child pid: %d\n", getpid());
        char* file = "ls";
        char* path = "/bin/ls";
        char* childArgv[2] = {"ls",NULL};
        char* childEnvp[2] = {"PATH=./customBin/",NULL};

        // execv接受绝对路径与参数向量(NULL结尾)
        execv(path, childArgv);
        // execl接受绝对路径与参数列表(NULL结尾)
        execl(path, childArgv[0], childArgv[1]);

        // 名称包含"p"的函数将会使用和Shell一致的文件搜索行为
        // 也就是使用当前进程的PATH环境变量
        execvp(file, childArgv);
        execlp(file, childArgv[0], childArgv[1]);

        // 名称包含"e"的函数将可以给出自定义环境变量(NULL结尾)
        execve(file, childArgv, childEnvp);
        execle(file, childArgv[0], childArgv[1], childEnvp[0], childEnvp[1]);

        // execvP 可以自定义搜索路径
        execvP(file, "./customBin/", childArgv);
    }

    wait(NULL);
    printf("parent pid: %d\n", getpid());

    return 0;
}
