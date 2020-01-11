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

//【01】知识点：exec函数族 + 无名管道PIPE + 文件描述符重定向
//编写一个程序，实现下述命令的执行效果：ls | wc -w

int main (void)
{
    pid_t pidd;
    int fd[2];

    //创建无名管道，在产生子进程前创建，这样才会被子进程继承
    if (-1 ==  pipe(fd))
    {
        perror ("create unnamed pipe failed");
        exit (-1);
    }
    
    //创建一个子进程
    pidd = fork ();
        
    if (0 == pidd)
    {
        //关闭子进程pipe的读端
        close (fd[0]);
        //将子进程pipe的写端重定向到标准输出，输出到标准输出，
        //也就相当于写入子进程pipe的写端
        dup2 (fd[1], STDOUT_FILENO);
        //执行ls命令
        execl ("/bin/ls", "ls", NULL);
    }
    else if (pidd > 0)
    {
        //关闭父进程pipe的写端
        close (fd[1]);
        //将父进程pipe的读端重定向到标准输入，从标准输入获取输入，
        //也就是从父进程pipe的读端获取输入
        dup2 (fd[0], STDIN_FILENO);
        execl ("/usr/bin/wc", "wc", "-w", NULL);
    }

    return 0;
}

