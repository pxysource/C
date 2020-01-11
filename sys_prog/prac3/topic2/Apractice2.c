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
void print (int sig)
{  
    printf ("sig = %d\n", sig);
}

int main (void)
{
    int i = 0;
    printf ("seller PID: %d\n", getpid ());

    /************************信号的三种处理方式**************************
    *1.默认sig信号
    *   signal (SIGHUP, SIG_DFL);
    *2.忽略sig信号
    *   signal (SIGINT, SIG_IGN);
    *3.为sig信号关联执行函数
    *   signal (SIGQUIT, func1);
    *********************************************************************/
    signal (SIGHUP, print);
    signal (SIGINT, print);
    signal (SIGQUIT, print);
    
    
    //延迟(阻塞)信号的响应
    sigset_t sigs;
    sigemptyset (&sigs);
    sigaddset (&sigs, SIGHUP);
    sigaddset (&sigs, SIGINT);
    sigaddset (&sigs, SIGQUIT);
    sigprocmask (SIG_SETMASK, &sigs, NULL);

    for(i = 0; i < 10; i++)
	{
		printf ("阻塞还剩%d秒...\n", 10 - i);
		sleep (1);
	}
    
    //解除对sigs中信号的阻塞
    sigprocmask (SIG_UNBLOCK, &sigs, NULL);

    // 静静地等待信号...
	while(1)
    {
		// 只要进程接收到信号pause就会返回
		pause();
    }

    return 0;
}

