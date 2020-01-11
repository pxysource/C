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

int main (void)
{
    pid_t pidd;
    int sig = 0;

    puts ("Please input process ID:");
    scanf ("%d", &pidd);
    
    //给指定的进程发送某个信号
    while (1)
    {   
        puts ("Please input signal signum:");
        scanf ("%d", &sig);
    
        kill (pidd, sig);
    }

    return 0;
}

