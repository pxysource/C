#include <iostream>
#include "bmp.h"
using namespace std;

int main()
{
    {
        Bmp b1("/pxy/cplusplus/1.bmp");
        b1.name();
        b1.getInfo();
        b1.info();
        b1.showInLcd();

        Bmp b2(b1);
        b2.name();
        b2.info();
    }

    return 0;
}
