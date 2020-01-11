//reader.c
#include "common.h"

int main (void)
{
    sem_t *sem_space;
    sem_t *sem_data;
    int shmid;
    char * shmaddr = NULL;
    
    //创建POSIX有名信号量
    sem_space = sem_open ("/space", O_CREAT, 00777, 1);
    sem_data = sem_open ("/data", O_CREAT, 00777, 0);

    shmid = shmget (ftok (PROJ_PATH, PROJ_SHMID), PROJ_SIZE, IPC_CREAT |
            00777);
    shmaddr = shmat (shmid, NULL, 0);

    while (1)
    {
        //申请数据资源
        puts ("\napply for data resource...");
        sem_wait (sem_data);
        //申请到数据资源
        puts ("get data resource.");

        printf ("reader: %s", shmaddr);

        //增加内存资源
        puts ("add memory resource...");
        sem_post (sem_space);
        //完成增加内存资源
        puts ("complete adding memory resource.");
    }

    shmdt (shmaddr);

    return 0;
}

