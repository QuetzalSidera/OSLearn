#include <stdio.h>

#include <unistd.h>

#include <assert.h>

#include <fcntl.h>

#include <sys/types.h>

int main(int argc, char* argv[])
{
    const int fd = open("./tmp/file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    printf("%d\n", fd);
    printf("Writing to file.txt is %d\n", fd);
    assert(fd > -1);
    const int rc = write(fd, "hello world\n", 13);
    assert(rc == 13);
    close(fd);
    return 0;
}
