//--->use exception

#include <iostream>
using namespace std;

double hmean (double x, double y);

int main()
{
    double x, y, z;

    cout << "Enter two numbers: " << endl;
    while (cin >> x >>y)
    {
        try{
            z= hmean(x, y);
        }
        catch(const char *s)
        {
            cout << s << endl;
            cout << "Enter a new pair of numbers: " << endl;
            continue;
        }

        cout << "Harmonic mean of " << x << " and " << y
             << " is " << z << endl;
        cout << "Enter next set of numbers (q to quit): " << endl;
    }

    return 0;
}

double hmean (double x, double y)
{
    if (x == -y)
    {
        throw "bad hmean() arguments: a=-b not allowed";
    }

    return 2.0 * x * y / (x + y);
}
