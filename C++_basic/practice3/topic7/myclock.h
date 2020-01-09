#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <iostream>
using namespace std;

class MyClock
{
private:
    unsigned int _minutes;
    unsigned int _seconds;
public:
    MyClock(unsigned int min=0, unsigned int sec=0);

    MyClock &operator++();
    MyClock operator++(int);
    void show ();
};

#endif // MYCLOCK_H
