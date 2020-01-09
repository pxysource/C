#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
using namespace std;

class ComplexNumber
{
    double _real;
    double _image;
public:
    ComplexNumber(double real_part=0, double image_part=0);
    ComplexNumber operator+(ComplexNumber &r);
    ComplexNumber operator-(ComplexNumber &r);
    ComplexNumber operator*(ComplexNumber &r);
    ComplexNumber operator/(ComplexNumber &r);

    friend ostream & operator<< (ostream &os, ComplexNumber &co);
};

#endif // COMPLEXNUMBER_H
