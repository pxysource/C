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

#define FIFO "/tmp/myfifo"

//编程实现两个程序：一个代表服务器，一个代表客户机。要求：
//A) 服务器采用精灵进程的方式在后台运行，常驻内存。
//   服务器创建并监视有名管道FIFO，一旦发现有数据，
//   服务器将其保存到一个指定的地方。
//B) 客户机每隔一段时间产生一个子进程，
//   这些子进程将当前系统时间和自身的PID写入有名管道FIFO就退出。

int main (void)
{
    int fd_fifo;
    int fd_txt;
    int readRet;
    char msg[32];
    pid_t pidd;
	int max_fd;
    int i;
	
    /*********************************************
	1. ignore the signal SIGHUP, prevent the
	   process from being killed by the shutdown
	   of the present controlling termination
	忽略HUP信号，防止在升仙途中被控制终端的关闭信号杀死
	**********************************************/
	signal(SIGHUP, SIG_IGN);

	/***************************************
	2. generate a child process, to ensure
	   successfully calling setsid()
	搞个孩子，确保可以执行setsid
	因为原来的父进程是组长，组长不允许调用setsid()
	****************************************/
	pidd = fork();
	if(pidd > 0)
    {
		exit (0);
    }

	/******************************************************
	3. call setsid(), let the first child process running
	   in a new session without a controlling termination
	创建一个新的会话，摆脱原来的控制终端
	*******************************************************/
	setsid ();

	/*************************************************
	4. generate the second child process, to ensure
	   that the daemon cannot open a terminal file
	   to become its controlling termination
	由于会话的创建者拥有再次打开控制终端的权力
	为了避免出现以上情况，再搞一个孩子
	**************************************************/
	pidd = fork ();
	if(pidd > 0)
    {
		exit(0);
    }

	/*********************************************************
	5. detach the daemon from its original process group, to
	   prevent any signal sent to it from being delivered
	将自己设置到一个新的进程组中
	避免收到原进程组的信号的影响
	**********************************************************/
	setpgrp ();

	/*************************************************
	6. close any file descriptor to release resource
	关闭所有的文件描述符，释放所有的资源
	**************************************************/
	max_fd = sysconf(_SC_OPEN_MAX);
	for (i = 0; i < max_fd; i++)
	{	
        close (i);
    }

	/******************************************
	7. clear the file permission mask to zero
	关闭文件权限掩码
	保证以后创建新文件时可以任意指定权限
	*******************************************/
	umask (0);

	/****************************************
	8. change the process's work directory,
	   to ensure it won't be uninstalled
	将精灵进程的工作路径修改为不可卸载的路径
	一般就设置为根路径即可
	*****************************************/
	chdir ("/");
    
    //管道文件不存在，则创建
    if (access(FIFO, F_OK))
    {
        //创建有名管道
        if (mkfifo (FIFO, 00666))
        {
            perror ("make named pipe error!");
            exit (-1);
        }
    }

    //打开有名管道
    fd_fifo = open (FIFO, O_RDONLY);
    
    //读写打开test.log文件，没有则创建
    fd_txt = open ("/tmp/test.log", O_RDWR | O_APPEND | O_CREAT, 00666);
    if (-1 == fd_txt)
    {
        perror ("open /tem/test.log error!");
        exit (-2);
    }

    bzero (msg, 0);

    while (1)
    {
        //阻塞读取管道数据，有数据就读取，没有则阻塞等待。
        readRet = read (fd_fifo, msg, sizeof(msg));
        //无写者，无数据，立即返回
        if (readRet < 0)
        {
            continue;
        }

        //将读取到的message写入log文件
        write (fd_txt, msg, readRet);
        bzero (msg, 0);
    }
    
    //关闭log文件
    close (fd_txt);
    //关闭管道文件
    close (fd_fifo);

    return 0;
}

