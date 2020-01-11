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

    puts ("Please input process ID");
    scanf ("%d", &pidd);
    while ('\n' != getchar ())
    {
        continue;
    }
    
    //给指定的进程发送某个信号
    while (1)
    {   
        if (15 == sig)
        {
            break;
        }
        kill (pidd, sig % 3 + 1);
        printf ("kill %d %d\n", pidd, sig % 3 + 1);  
        sig++;
    }

    return 0;
}

