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

void drive (int sig)
{
    pid_t pidd;

    switch (sig)
    {
        case SIGUSR1:
            printf ("开车\n");
            break;
        case SIGUSR2:
            printf ("靠站\n");
            break;
        case SIGTSTP:
            puts ("Please input seller process ID:");
            scanf ("%d", &pidd);
            while ('\n' != getchar ())
            {
                continue;
            }
            kill (pidd, SIGUSR1);
            exit (0);
    }
}

int main (void)
{
    printf ("driver PID: %d\n", getpid ());

    signal (SIGUSR1, drive);
    signal (SIGUSR2, drive);
    signal (SIGTSTP, drive);
    
	while(1)
    {
		pause();
    }

    return 0;
}

