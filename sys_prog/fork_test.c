#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//测试子进程从父进程那里得到了哪些哪些
int main (void)
{
    int a = 1;
    char * ptr = "process test";
    char * str = (char *)malloc (20 * sizeof(char));
    sprintf (str, "%s", "ni hao");
    pid_t pidddd;

    pidddd = fork ();

    printf ("a = %d\n", a);
    printf ("ptr = %s\n", ptr);
    printf ("str = %s\n", str);
    printf ("Hello world\n");
    printf ("pidddd = %d\n", pidddd);

    

    while (1);


    return 0;
}

