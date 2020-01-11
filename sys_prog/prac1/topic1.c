#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

//使用进程复刻技术，在一个程序中同时不断循环输出阿拉伯数字、英文字母
int main (void)
{
    char i = '0';
    char alphabet1 = 'A';
    char alphabet2 = 'a';

    pid_t pidd = fork ();
    
    if (pidd > 0)
    {
        while (1)
        {
            fprintf (stderr, "%c\t", i++);
            if (('9' + 1) == i)
            {
                i = '0';
            }

            sleep (1);
        }
    }
    else if (0 == pidd)
    {
        pidd = fork ();
        
        if (pidd > 0)
        {
            while (1)
            {
                fprintf (stderr, "%c\t", alphabet1++);
                if (('Z' + 1) == alphabet1)
                {
                    alphabet1 = 'A';
                }

                sleep (1);
            }
        }
        else if (0 == pidd)
        {
            while (1)
            {
                fprintf (stderr, "%c\t", alphabet2++);
                if (('z' + 1) == alphabet2)
                {
                    alphabet2 = 'a';
                }

                sleep (1);
            }
        }
    }

    return 0;
}

