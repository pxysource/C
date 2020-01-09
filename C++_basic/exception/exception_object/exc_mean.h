#ifndef EXC_MEAN_H
#define EXC_MEAN_H

#include <iostream>
using std::cout;
using std::endl;

class bad_hmean
{
private:
    double v1;
    double v2;

public:
    bad_hmean (double a=0.0, double b=0.0):v1(a), v2(b){}
    void mesg();
};

inline void bad_hmean::mesg()
{
    cout << "hmean(" << v1 << ", " << v2 << "): "
         << "invalid arguments: a=-b " << endl;
}

class bad_gmean
{
public:
    double v1;
    double v2;
    bad_gmean(double a=0.0, double b=0.0):v1(a), v2(b){}
    const char *mesg();

};

inline const char *bad_gmean::mesg()
{
    return "gmean() arguments should be >= 0\n";
}

#endif // EXC_MEAN_H
