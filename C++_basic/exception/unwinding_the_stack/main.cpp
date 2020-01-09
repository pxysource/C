//unwinding the stack --->栈解退
#include <iostream>
#include <cmath>
#include "exc_mean.h"

using namespace std;

class demo
{
private:
    string word;
public:
    demo(const string & str)
    {
        word = str;
        cout << "demo " << word << " created" << endl;
    }
    ~demo()
    {
        cout << "demo " << word << " destroyed" << endl;
    }
    void show()
    {
        cout << "demo " << word << " lives!" << endl;
    }
};

double hmean(double x, double y);
double gmean(double x, double y);
double means(double x, double y);

int main()
{
    double x, y, z;

    {
        demo d1("found in block in main()");
        while (cin >> x >> y)
        {
            try{
                z = means(x, y);
                cout << "The mean mean of " << x << " and " << y
                     << " is " << z << endl;
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
        d1.show();
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

double means(double x, double y)
{
    double am, hm, gm;
    demo d2("found in means");
    am = (x + y) / 2.0;

    try{
        hm = hmean(x, y);
        gm = gmean(x, y);
    }
    catch (bad_hmean & bh)
    {
        bh.mesg();
        cout << "Caught in means()" << endl;
        throw;//rethrows the exception
    }

    d2.show();
    return (am + hm + gm) / 3.0;
}


