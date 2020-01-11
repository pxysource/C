#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//编程产生一个进程扇，即一个父进程产生一系列子进程，
//要求每个子进程输出自己的PID后退出，
//父进程等所有子进程都退出之后，也输出自己的PID，然后退出
int main (void)
{
    int i = 0;
    int status;
    pid_t pidd = 0;

    //创建一个子进程
    pidd = fork ();
    
    //创建一些子进程，而不会创建子进程的子进程
    while (i++ <3)
    {
        if (pidd > 0)
        {
           pidd = fork ();
        
        }
    }

    for (i = 0; i < 4; i++)
    {
        //父进程阻塞等待子进程的退出
        //若没有子进程,则直接返回-1,不等待
        if (wait (&status) > 0)
        {
            //如果子进程正常退出，该宏为真
            if (WIFEXITED (status))
            {
                //获取子进程退出值
                printf ("status = %d\n", WEXITSTATUS (status));    
            }
        }
    }

    //打印本进程id和父进程的id
    printf ("pid = %d, ppid = %d\n", getpid (), getppid ());

    exit (0);
}

