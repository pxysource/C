#include "common.h"

//semid:信号量集合的ID
//num  :信号量元素的序号
void sem_p (int semid, int num)
{
    int ret = 0;
    struct sembuf buf;
    bzero (&buf, sizeof(buf));

    buf.sem_num = num;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    
    ret = semop (semid, &buf, 1);
    if (-1 == ret)
    {
        perror ("Function sem_p() (semop() ) error");
    }
}

void sem_v (int semid, int num)
{
    int ret = 0;
    struct sembuf buf;
    bzero (&buf, sizeof(buf));

    buf.sem_num = num;
    buf.sem_op = +1;
    buf.sem_flg = 0;
    
    ret = semop (semid, &buf, 1);
    if (-1 == ret)
    {
        perror ("Function sem_v() (semop() ) error");
    }
}

//初始化信号量集合中的指定元素
void init_sem (int semid, int num, int value)
{
    union semun a;
    a.val = value;
    semctl (semid, num, SETVAL, a);
}
