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
int main (void)
{
    char *path = "/tmp/myfifo";
    int fd;

    if (access(path, F_OK))
    {
        if (mkfifo(path, 00666))
        {
            perror ("make named pipe error!");
            exit (-1);
        }
    }
    
    fd = open (path, O_RDONLY);

    while (1);

    close (fd);

    return 0;
}

