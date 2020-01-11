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
int main(void)
{
    pid_t pidd;
    int fd[2];
    int mode;

    //创建无名管道
    pipe (fd);

    pidd = fork ();
    
    if (0 == pidd)
    {
        char a = 'a';
        int i = 0;
        int writeRet = 0;
        //关闭子进程读端
        close (fd[0]);

        //非阻塞，设置无名管道写端非阻塞
        mode = fcntl (fd[1], F_GETFL);
        mode |= O_NONBLOCK;
        fcntl (fd[1], F_SETFL, mode);
        
        while (1)
        {
            writeRet = write (fd[1],&a, sizeof(char));
            if (1 != writeRet)
            {
                printf ("%d \n", i);
                break;
            }
            i++;
        }

        //设置无名管道读端阻塞
        mode = fcntl (fd[1], F_GETFL);
        mode &= ~O_NONBLOCK;
        fcntl (fd[1], F_SETFL, mode);
    }
    else if (pidd > 0)
    {
        wait (NULL);
    }

    exit (0);
}

