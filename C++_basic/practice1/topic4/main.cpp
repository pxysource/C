/********************************************************
 *4.编写一个程序，要求用户不断输入两个数字，求这两个数的调和平均数。
 * ******************************************************/

#include <iostream>
using namespace std;

int main ()
{
    int a;
    int b;
    int var;

    while (1)
    {
        cout << "Please input two integer: ";
        cout << " (enter 0 to exit)" << endl;
        cin >> a >> b;

        if (0 == a || 0 == b)
        {
            cout << "exit" << endl;
            break;
        }

        var = 2 * a * b / (a + b);
        cout << "harmonic average (a,b): " << var << endl;
    }

    return 0;
}
