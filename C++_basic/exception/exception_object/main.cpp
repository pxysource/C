//将对象用作异常类型

#include <iostream>
#include <cmath>
#include "exc_mean.h"
using namespace std;

double hmean(double x, double y);
double gmean(double x, double y);

int main()
{
    double x, y, z;

    cout << "Enter two numbers: " << endl;
    while (cin >> x >> y)
    {
        try{
            z = hmean(x, y);
            cout << "Harmonic mean of " << x << " and " << y
                 << " is " << z << endl;
            cout << "Geometric mean of " << x << " and " << y
                 << " is " << gmean(x, y) << endl;
            cout << "Enter next set of numbers (q to quit): " << endl;
        }
        catch (bad_hmean & bh)
        {
            bh.mesg();
            cout << "Try again: " << endl;
            continue;
        }
        catch (bad_gmean & bg)
        {
            cout << bg.mesg();
            cout << "Value used: " << bg.v1 << ", " << bg.v2 << endl;
            cout << "Sorry, you don't get to pay any more." << endl;
            break;
        }
    }

    cout << "Bye!" << endl;
    return 0;
}

double hmean(double x, double y)
{
    if (x == -y)
    {
        throw bad_hmean(x, y);
    }

    return 2.0 * x * y / (x + y);
}

double gmean(double x, double y)
{
    if (x < 0 || y < 0)
    {
        throw bad_gmean(x, y);
    }

    return sqrt(x * y);
}
