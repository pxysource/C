#include <iostream>
#include <cmath>
using namespace std;

class Point
{
private:
    double _x;
    double _y;

public:
    Point (){ _x = 0; _y = 0; cout << "Point default constructor called" << endl;}
    Point (double x, double y):_x(x), _y(y){ cout << "Point constructor called" << endl;}
    ~Point (){cout << "point destructor called" << endl;}
    double x (){return _x;}
    double y (){return _y;}
};

class Line
{
private:
    Point _p1;
    Point _p2;
    double _length;

public:
    Line (){cout << "Line default constructor called" << endl;}
    Line (Point &p1, Point &p2):_p1(p1), _p2(p2){cout << "Line 2th constructor called" << endl;}
    Line (double p1x, double p1y, double p2x, double p2y):_p1(p1x, p1y), _p2(p2x, p2y){
                                                          cout << "Line 1th constructor called" << endl;}
    ~Line (){cout << "Line destructor called" << endl;}
    double length ();

};

double Line::length ()
{
    double tmpx = (_p1.x() - _p2.x()) * (_p1.x() - _p2.x());
    double tmpy = (_p1.y() - _p2.y()) * (_p1.y() - _p2.y());
    _length = sqrt (tmpx + tmpy);
    cout << "length: " << _length << endl;
    return _length;
}

int main()
{
    {
        Line l1(1, 1, 2, 2);
        l1.length();
    }

    {
        Point p1(1, 1);
        Point p2(2, 2);

        Line l2(p1, p2);
        l2.length();
    }

    return 0;
}
