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
#include <signal.h>

//用信号集相关函数，信号发送和注册函数等相关知识，编写代码验证以下结论：
//A) 进程的信号挂起队列中，没有相同的信号（即相同的信号会被丢弃）。
//B) 进程在响应信号时，信号会相互嵌套。
//C) 挂起信号不会被子进程继承，但信号阻塞掩码会被继承。

void print1 (int sig)
{  
    int i = 0;
    while (i++ < 10)
    {
        sleep (1);
        printf ("sig = 1\n");
    }
}

void print2 (int sig)
{ 
    int i = 0;
    while (i++ < 10)
    {
        sleep (1);
        printf ("sig = 2\n");
    }
}

void print3 (int sig)
{  
    int i = 0;
    while (i++ < 10)
    {
        sleep (1);
        printf ("sig = 3\n");
    }
}

int main (void)
{
    printf ("seller PID: %d\n", getpid ());

    /************************信号的三种处理方式**************************
    *1.默认sig信号
    *   signal (SIGHUP, SIG_DFL);
    *2.忽略sig信号
    *   signal (SIGINT, SIG_IGN);
    *3.为sig信号关联执行函数
    *   signal (SIGQUIT, func1);
    *********************************************************************/
    signal (SIGHUP, print1);
    signal (SIGINT, print2);
    signal (SIGQUIT, print3);

    // 静静地等待信号...
	while(1)
    {
		// 只要进程接收到信号pause就会返回
		pause();
    }

    return 0;
}

