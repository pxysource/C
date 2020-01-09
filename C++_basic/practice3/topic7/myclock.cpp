#include "myclock.h"
#include <iomanip>

MyClock::MyClock(unsigned int min, unsigned int sec)
{
    _minutes = min;
    _seconds = sec;
}

MyClock &MyClock::operator++()
{
    this->_seconds++;
    this->_minutes += this->_seconds / 60;
    if (60 == this->_seconds)
    {
        this->_seconds = 0;
    }

    return *this;
}

MyClock MyClock::operator++(int)
{
   MyClock tmp;

   tmp._seconds = this->_seconds;
   tmp._minutes = this->_minutes;
   this->_seconds++;
   this->_minutes += this->_seconds / 60;
   if (60 == this->_seconds)
   {
       this->_seconds = 0;
   }

   return tmp;
}

void MyClock::show()
{

    cout << "minutes:seconds = ";
    //std::setfill():设置输出的填充字符
    //std::setw():设置输出的宽度
    cout << std::setfill('0') << std::setw(2) << _minutes;
    cout << ":";
    cout << std::setfill('0') << std::setw(2) << _seconds << endl;
}
