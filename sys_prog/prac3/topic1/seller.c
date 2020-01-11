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

/*
void func1 (int sig)
{
    printf ("sig :%d called...\n", sig);
}
*/
//开车
void send (int sig)
{
    if (SIGUSR1 == sig)
    {
        printf ("到总站,全部下车\n");
        exit (0);
    }

    pid_t pidd;
    puts ("Please input driver process ID:");
    scanf ("%d", &pidd);

    while ('\n' != getchar ())
    {
        continue;
    }

    switch (sig)
    {
        case SIGINT:
            kill (pidd, SIGUSR1);
            break;
        case SIGQUIT:
            kill (pidd, SIGUSR2);
            break;
    }
}

int main (void)
{
//    int i = 0;
    printf ("seller PID: %d\n", getpid ());

    /************************信号的三种处理方式**************************
    *1.默认sig信号
    *   signal (SIGHUP, SIG_DFL);
    *2.忽略sig信号
    *   signal (SIGINT, SIG_IGN);
    *3.为sig信号关联执行函数
    *   signal (SIGQUIT, func1);
    *********************************************************************/
    signal (SIGINT, send);
    signal (SIGQUIT, send);
    signal (SIGUSR1, send);
    
    /*
    //延迟(阻塞)信号的响应
    sigset_t sigs;
    sigemptyset (&sigs);
    sigaddset (&sigs, SIGHUP);
    sigaddset (&sigs, SIGINT);
    sigprocmask (SIG_SETMASK, sigs, NULL);

    for(i = 0; i < 10; i++)
	{
		printf ("阻塞还剩%d秒...\n", 10 - i);
		sleep (1);
	}
    
    //解除对sigs中信号的阻塞
    sigprocmask (SIG_UNBLOCK, sigs, NULL);
    */

    // 静静地等待信号...
	while(1)
    {
		// 只要进程接收到信号pause就会返回
		pause();
    }

    return 0;
}

