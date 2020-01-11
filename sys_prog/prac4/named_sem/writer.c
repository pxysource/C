//writer.c
#include "common.h"

static sem_t *sem_space;

//通过ctrl+c中断(其他结束进程的信号类似)进程时候,
//会导致出现申请的内存资源没有写入数据,
//另一边没有申请到数据也就不会释放内存,
//就出现了内存资源和数据资源都为0的情况,
//下一次运行时侯两边的进程都阻塞在申请资源,
//通过响应函数end响应SIGINT信号(其他信号类似)来将内存资源增加
//即回到初始状态或其他两边不同时阻塞的情况
static void end (int sig)
{
    printf ("end...\n");
    sem_post (sem_space);
    exit (0);
}


int main (void)
{   
//    sem_t *sem_space;
    sem_t *sem_data;
    int shmid;
    char * shmaddr = NULL;
    
    //创建POSIX有名信号量
    sem_space = sem_open ("/space", O_CREAT, 00777, 1);
    sem_data = sem_open ("/data", O_CREAT, 00777, 0);
    
    

    shmid = shmget (ftok (PROJ_PATH, PROJ_SHMID), PROJ_SIZE, IPC_CREAT |
            00777);
    shmaddr = shmat (shmid, NULL, 0);

    signal (SIGINT, end);

    while (1)
    {
        //申请内存资源
        puts ("\napply for memory resource...");
        sem_wait (sem_space);
        //申请到内存资源
        puts ("get memory resource.");

        bzero (shmaddr, PROJ_SIZE);
        printf ("writer: ");
        fgets (shmaddr, PROJ_SIZE, stdin);

        //增加数据资源
        puts ("add data resource...");
        sem_post (sem_data);
        //完成增加数据资源
        puts ("complete adding data resource.");
    }

    shmdt (shmaddr);
    
    pause ();

    return 0;
}

