#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//编写程序，检测无名管道和有名管道的默认缓冲区大小
//fifo
int main (void)
{
    char *myfifo = "/tmp/myfifo";
    int fd;
    int mode;
    int writeRet;
    int i = 0;
    char a = 'a';

    if (access(myfifo, F_OK))
    {
        if (mkfifo (myfifo, 00666))
        {
            perror ("make named pipe error!");
            exit (-1);
        }
    }

    fd = open (myfifo, O_WRONLY);

    //非阻塞
    mode = fcntl (fd, F_GETFL);
    mode |= O_NONBLOCK;
    fcntl (fd, F_SETFL, mode);

    while (1)
    {
        writeRet = write (fd, &a, sizeof(a));

        if (1 != writeRet)
        {
            printf ("%d \n", i);
            break;
        }
        i++;
    }

    //阻塞
    mode = fcntl (fd, F_GETFL);
    mode &= ~O_NONBLOCK;
    fcntl (fd, F_SETFL, mode);

    close (fd);

    return 0;
}

