#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void)
{
    printf("[%d]: before fork\n", getpid());

    pid_t pidd;
    pidd = fork();

    printf("[%d]: after fork\n", getpid());

    return 0;
}

