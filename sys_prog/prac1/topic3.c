#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//编程产生一个进程链，父进程派生一个子进程后，输出自己的PID，然后退出，
//该子进程继续派生子进程，然后打印PID，然后退出，以此类推。
//要求实现两个版本：
//    A) 父进程比子进程先打印PID。
//    B) 子进程比父进程先打印PID。

//A
int main1 (void)
{
    int i = 0;
    pid_t piddd;

    for (i = 0; i < 10; i++)
    {
        printf ("pid = %d, ppid = %d\n", getpid (), getppid ());
        piddd = fork ();

        if (piddd > 0)
        {
            exit (0);
        }
        else if (0 == piddd)
        {
            continue;
        }
    }

    return 0;
}

//B
int main (void)
{
    int i = 0;
    pid_t piddd;

    for (i = 0; i < 10; i++)
    {
        piddd = fork ();

        if (piddd > 0)
        {
            //父进程阻塞等待子进程退出
            //NULL：表示不在乎子进程的退出值
            wait (NULL);

            printf ("pid = %d, ppid = %d\n", getpid (), getppid ());
            exit (0);
        }

        if (0 == piddd)
        {
            continue;
        }
    }

    return 0;
}
