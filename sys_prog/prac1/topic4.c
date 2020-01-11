#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

//编写一个程序，使之产生一个子进程c，并使用exec函数族中的任意一个版本，使
//子进程c执行系统命令ls -l去查看某个文件的信息，父进程判断子进程是否执行成功
int main (void)
{
    pid_t pidd;

    pidd = fork ();

    if (0 == pidd)
    {
        execl ("/bin/ls", "ls", "xxxxx", "-l", "-i", NULL);
        //execl ("/bin/ls", "ls", "-l", NULL);
    }

    if (pidd > 0)
    {
        int status;
        wait (&status);

        //如果子进程正常退出，该宏为真
        if (WIFEXITED (status))
        {
            //子进程执行成功和其怎么退出没关系，退出只是表示他怎么退出，并不能说明执行的状态，
            //所以根据返回值来确定执行成功与否
            //子进程的返回值为0，表示子进程执行成功
            if (!WEXITSTATUS (status))
            {    
                printf ("\"ls\" succeed: %d\n", WEXITSTATUS (status));
            }
            //子进程的返回值不为0，表示执行错误
            else
            {
                printf ("\"ls\" error.\n");
            }
        }
        //子进程异常退出
        else
        {
            printf ("ls 异常退出!!\n");
        }
    }
   
    return 0;
}

