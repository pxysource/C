//writer.c
#include "common.h"

static int semid;

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
    init_sem (semid, SPACE, 1);
    exit (0);
}

int main (void)
{
    int shmid;
    char *shmaddr = NULL;
    
    // 创建信号量,2:总共2个信号量
    // 信号量不存在就创建；存在就报错
    semid = semget (ftok (PROJ_PATH, PROJ_SEMID), 2, IPC_CREAT |
            IPC_EXCL | 00666);
    if (-1 != semid)
    {   
        //初始化sytem-v信号量中的每个元素
        printf ("Initialize semaphore...\n");
        init_sem (semid, DATA, 0);
        init_sem (semid, SPACE, 1);
    }
    else
    {
        // 获取信号量的ID
        semid = semget (ftok (PROJ_PATH, PROJ_SEMID), 2, 00666); 
    }

    shmid = shmget (ftok (PROJ_PATH, PROJ_SHMID), SHM_SIZE, IPC_CREAT |
            00666);
    shmaddr = shmat (shmid, NULL, 0);

    signal (SIGINT, end);

    while (1)
    {
        //申请内存资源
        puts ("\napply for memory resource...");
        sem_p (semid, SPACE);
        //申请到内存资源
        puts ("get memory resource.");

        bzero (shmaddr, SHM_SIZE);
        printf ("writer: ");
        fgets (shmaddr, SHM_SIZE, stdin);

        //增加数据资源
        puts ("add data resource...");
        sem_v (semid, DATA);
        //完成增加数据资源
        puts ("complete adding data resource.");
    }

    shmdt (shmaddr);
    
    pause ();

    return 0;
}

