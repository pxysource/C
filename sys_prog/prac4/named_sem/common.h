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
#define PROJ_SHMID  2
#define SHN_SIZE    1024
//#define BUFSIZE   64

#endif
