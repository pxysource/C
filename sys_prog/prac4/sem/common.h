#ifndef _COMMON_H_
#define _COMMON_H_

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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/sem.h>
#include <semaphore.h>

/***********************************Macro*******************************/
#define PROJ_PATH   "."
#define PROJ_SEMID  1
#define PROJ_SHMID  2
#define DATA        0
#define SPACE       1
#define SHM_SIZE   1024
//#define BUFSIZE   64

/***********************************Function****************************/
void sem_p (int semid, int num);

void sem_v (int semid, int num);

void init_sem (int semid, int num, int value);

/***********************************Data********************************/
union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

#endif
