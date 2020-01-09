#include <iostream>
#include "bmp.h"

int main()
{
    Bmp pix1("test.bmp");
    pix1.bmpName();
    pix1.bmpInfo();

    Bmp pix2(pix1);
    pix2.bmpName();
    pix2.bmpInfo();

    Bmp pix3;
    pix3 = pix1;
    pix3.bmpName();
    pix3.bmpInfo();
    return 0;
}
