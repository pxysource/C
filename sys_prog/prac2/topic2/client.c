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
#include <time.h>
#include <signal.h>

#define FIFO "/tmp/myfifo"

//编程实现两个程序：一个代表服务器，一个代表客户机。要求：
//A) 服务器采用精灵进程的方式在后台运行，常驻内存。
//   服务器创建并监视有名管道FIFO，一旦发现有数据，
//   服务器将其保存到一个指定的地方。
//B) 客户机每隔一段时间产生一个子进程，
//   这些子进程将当前系统时间和自身的PID写入有名管道FIFO就退出。

int main (void)
{
    int fd;
    //子进程退出状态
    int status;
    char msg[32];
    pid_t pidd;
    
    bzero (msg, 32);

    //如果管道文件不存在，就创建
    //返回0表示存在
    if (access (FIFO, F_OK))
    {
        if (mkfifo (FIFO, 00666))
        {
            perror ("make named pipe error!");
            exit (-1);
        }
    }

    //以只写方式打开管道，客户端为写者
    fd = open (FIFO, O_WRONLY);

    //服务器退出时，此时管道有写者，无读者，写者进程收到SIGPIPE信号
    //写者进程也就是这里的子进程
    signal (SIGPIPE, SIG_DFL);
    
    while (1)
    {
        pidd = fork ();

        if (0 == pidd)
        {
            time_t now;
            struct tm *timenow;

            time (&now);
            timenow = localtime (&now);

            sprintf (msg, "%d:%s", getpid(), asctime (timenow));
            write (fd, msg, sizeof(msg));
            printf ("%s", msg);
        
            //子进程，向管道中写入信息后，就退出
            break;
        }
        else if (pidd > 0)
        {
            //等待子进程退出
            wait (&status);
            
            //子进程被信号终止，如果被信号SIGPIPE终止，则退出客户端
            if (WIFSIGNALED(status) && SIGPIPE == WTERMSIG(status))
            {
                close (fd);
                break;
            }

            //延时1s产生子进程
            sleep (1);
            continue;
        }
    }

    exit (0);
}

