#include <iostream>
using namespace std;

class Circle
{
private:
    double _radius;
    const double _pi = 3.14;

public:
    Circle (double r=0.0):_radius(r){}
    void setRadius (double r){_radius = r;}
    double radius (){return _radius;}
    double area ()const{return _pi * _radius * _radius;}
    friend ostream &operator<<(ostream &os, Circle &r);
};

ostream &operator<<(ostream &os, Circle &r)
{
    os << "Circle radius: " << r._radius;
    os << " Circle area: " << r.area();

    return os;
}

class Cylinder
{
private:
    Circle _c1;
    double _height;

public:
    Cylinder (double h=0.0, double r=0.0):_height(h){_c1.setRadius(r);}
    void setHeight (double h){_height = h;}
    double height (){return _height;}
    double circleArea (){return _c1.area();}
    double volume (){return circleArea() * _height / 3;}
    friend ostream &operator<<(ostream &os, Cylinder &r);

};

ostream &operator<<(ostream &os, Cylinder &r)
{
    os << r._c1 << endl;
    os << "Cylinder height: " << r._height;
    os << " Cylinder volume: " << r.volume();

    return os;
}

int main()
{
    Circle c1(2);
    cout << c1 << endl;

    Cylinder cy1(3, 2);
    cout << cy1 << endl;

    return 0;
}
