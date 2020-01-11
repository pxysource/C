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

    //1.忽略控制终端的关闭信号，防止控制终端被关闭时，导致当前会话的进程退出
    signal (SIGHUP, SIG_IGN);

    //2.产生一个子进程
    //由于原来的进程为进程组的第一个进程，为进程组组长，组长不能创建会话（session）
    if (fork() > 0)
    {
        exit (0);
    }

    //3.创建一个新的会话，摆脱原来终端的控制
    setsid ();

    //4.由于会话的创建者，为会话的“会长”，有再次打开终端的权利
    //为了避免这种情况出现，创建一个子进程（这一步，不是必要的）
    if (fork() > 0)
    {
        exit (0);
    }

    //5.加入一个新的进程组
    //避免收到原进程组的信号的影响（这一步，不是必要的）
    setpgrp ();

    //关闭所有的文件描述符，释放所有的资源
    int maxfd = sysconf(_SC_OPEN_MAX);
    for (int i = 0; i < maxfd; i++)
    {
        close (i);
    }

    //关闭文件权限掩码
    //保证以后创建新文件时可以任意指定权限
    umask (0);

    //将精灵进程的工作路径修改为不可卸载的路径
	//一般就设置为根路径即可
    chdir ("/");

    //这里的暂停，仅测试用，实际使用模板时，请删除
    pause ();

    return 0;
}

