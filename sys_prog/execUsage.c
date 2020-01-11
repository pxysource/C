#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (void)
{
    pid_t pidd;

    pidd = fork ();

    if (pidd > 0)
    {
        printf ("[%d]: I am parent\n", getpid());
    }

    if (0 == pidd)
    {
        printf ("[%d]: I am child\n", getpid());
        execl ("/bin/ls", "ls", NULL);

        printf ("Never be printed.\n");
    }

    return 0;
}

