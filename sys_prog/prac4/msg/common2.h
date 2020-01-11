#ifndef _COMMON2_H_
#define _COMMON2_H_

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
#include <sys/msg.h>

#define PROJ_PATH   "."
#define PROJ_ID     2
#define J2R         100
#define R2J         200

struct msgbuf{
    long type;
    char data[1024];
};

#endif
