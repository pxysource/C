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

//1.编写两个程序，一个代表司机，一个代表售票员。他们之间的交互如下：
//A) 用信号SIGINT向售票员发出开车命令，售票员收到该信号后发送信号
//   SIGUSR1给司机，司机捕捉到SIGUSR1之后输出“开车”。
//B) 用信号SIGQUIT向售票员发出靠站命令，售票员收到该信号后发信号
//   SIGUSR2给司机，司机捕捉到SIGUSR2之后输出“靠站”。
//C) 用信号SIGTSTP向司机发出达到总站的提示，司机收到该信号后
//   发送信号SGUSR1给售票员并退出，售票员捕捉到该信号之后输出“到总站，
//   全部下车”后退出。

int main (void)
{
    pid_t pidd;
    int sig;

    //给指定的进程发送某个信号
    while (1)
    {
        puts ("Please input process ID and signum:");
        scanf ("%d", &pidd);
        scanf ("%d", &sig);
        while ('\n' != getchar ())
        {
            continue;
        }
    
        kill (pidd, sig);

        if (SIGTSTP == sig)
        {
            break;
        }
    }

    return 0;
}

