//reader.c
#include "common.h"

int main (void)
{
    int semid;
    int shmid;
    char *shmaddr = NULL;
    //创建信号量,2:总共2个信号量
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
        semid = semget (ftok (PROJ_PATH, PROJ_SEMID), 2, 00666); 
    }

    shmid = shmget (ftok (PROJ_PATH, PROJ_SHMID), SHM_SIZE, IPC_CREAT |
            00666);
    shmaddr = shmat (shmid, NULL, 0);

    while (1)
    {
        //申请数据资源
        puts ("\napply for data resource...");
        sem_p (semid, DATA);
        //申请到数据资源
        puts ("get data resource.");

        printf ("reader: %s", shmaddr);

        //增加内存资源
        puts ("add memory resource...");
        sem_v (semid, SPACE);
        //完成增加内存资源
        puts ("complete adding memory resource.");
    }

    shmdt (shmaddr);

    return 0;
}

