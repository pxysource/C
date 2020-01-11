//rose.c
#include "common2.h"

int main (void)
{
    int msgid;
    pid_t pidd;
    struct msgbuf msg;

    key_t key_msg = ftok (PROJ_PATH, PROJ_ID);
    if (-1 == key_msg)
    {
        perror ("Generated System v IPC error!");
        return -1;
    }

    msgid = msgget (key_msg, IPC_CREAT | 00666);

    pidd = fork ();

    if (0 == pidd)
    {
        while (1)
        {
            bzero (&msg, sizeof(msg));
            msgrcv (msgid, &msg, 1024, J2R, 0);
            printf ("come from jack: %s", msg.data);
        }
    }
    else if (pidd > 0)
    {
        while (1)
        {
            msg.type = R2J;
            fgets (msg.data, 1024, stdin);
            msgsnd (msgid, &msg, strlen(msg.data), 0);
        }
    }

    return 0;
}

