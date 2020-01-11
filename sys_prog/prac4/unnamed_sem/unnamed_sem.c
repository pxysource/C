#include "common.h"

static sem_t space;
static sem_t data;

static void * reader (void * arg)
{
    while (1)
    {
        sem_wait (&data);

        printf ("reader: %s", (char *)arg);

        sem_post (&space);
    }

    pthread_exit (NULL);
}

int main (void)
{
    pthread_t tid;
    char buf[128];

    //初始化POSIX无名信号量
    sem_init (&space, 0, 1);
    sem_init (&data, 0, 0);

    pthread_create (&tid, NULL, reader, (void *)buf);
    
    while (1)
    {
        sem_wait (&space);
        
        bzero (buf, 128);
        printf ("writer: ");
        fgets (buf, sizeof(buf), stdin);

        sem_post (&data);
    }
    
    return 0;
}

