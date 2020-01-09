#include <iostream>
#include "myclock.h"
#include <unistd.h>
using namespace std;

int main()
{
    MyClock c1;
    MyClock c2;

    while (1)
    {
        (c1++).show();
        (++c2).show();
        sleep (1);
    }

    return 0;
}
