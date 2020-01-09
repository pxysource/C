#include <iostream>
#include "complexnumber.h"
using namespace std;

int main()
{
    ComplexNumber result;
    ComplexNumber z1(1, 2);
    cout << "z1 = " << z1 << endl;

    ComplexNumber z2;
    cout << "z2 = " << z2 << endl;

    result = z1 + z2;
    cout << "z1 + z2 = " << result << endl;

    result = z1 - z2;
    cout << "z1 - z2 = " << result << endl;

    result = z1 * z2;
    cout << "z1 * z2 = " << result << endl;

    //如果z2为0, 则会出错, 返回nan:not a number
    result = z1 / z2;
    cout << "z1 / z2 = " << result << endl;

    return 0;

}
