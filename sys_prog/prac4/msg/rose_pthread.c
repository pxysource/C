//rose_pthread.c
#include "common22.h"

static int msgid;

void *routine (void * arg)
{
    //将自己设置为分离状态
    //pthread_detach (pthread_self ());
    struct msgbuf msg;
    
    printf ("child thread tid: %ld\n", pthread_self());
    
    while (1)
    {
        msg.type = R2J;
        fgets (msg.data, 1024, stdin);
        msgsnd (msgid, &msg, strlen(msg.data), 0);
    }

    //退出线程,可以带上返回值
    printf ("child thread %ld exit...\n", pthread_self());
    pthread_exit ((void *) "child thread exit");
    
    //退出进程
    //exit (0);
}

int main (void)
{
    pthread_t tid;
    pthread_attr_t attr;
    void *retval = NULL;
    int err;
    struct msgbuf msg;

    printf ("rose's main tid: %ld\n", pthread_self ());
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

    pthread_create (&tid, &attr, routine, NULL);
    usleep (100 * 1000);
    
    msgid = msgget (ftok (PROJ_PATH, PROJ_ID), IPC_CREAT | 00666);

    while (1)
    {
        bzero (&msg, sizeof(msg));
        msgrcv (msgid, &msg, 1024, J2R, 0);
        printf ("come from jack: %s", msg.data);
    }
    
    err = pthread_join (tid, &retval);
    if (0 == err)
    {
        printf ("join thread %ld succeed, return value: %s\n", tid, (char *)retval);    
    }
    else
    {
        printf ("join thread %ld fault: %s\n", pthread_self(), strerror(err));
    }
    
    //退出主线程
    printf ("main thread exit.\n");
    pthread_exit (NULL);

    //退出进程
    //return 0;
}

