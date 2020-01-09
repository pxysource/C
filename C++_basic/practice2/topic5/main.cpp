#include <iostream>
using namespace std;

class Shape
{
public:
    double x;
    double y;

public:
    Shape (){x = 0; y = 0;}
    Shape (double x, double y):x(x), y(y){cout << "Shape" << endl;}
    virtual void area ()=0;
    virtual void perimeter ()=0;
    virtual void showInfo ()=0;
};

class Circle : public Shape
{
private:
    const double PI = 3.14;
    double radius;

public:
    Circle (){radius = 1;}
    Circle (double r):radius(r){}
    //x,y要写在前面,因为要先构造基类Shape,再构造Circle派生类
    Circle (double x, double y, double r):Shape(x, y), radius(r){}
    void area () override {cout << "circle area: " << PI * radius * radius << endl;}
    void perimeter () override {cout << "circle perimeter: " << 2 * PI * radius << endl;}
    void showInfo () override {cout << "circle x: " << x << endl;\
                               cout << "       y: " << y << endl;\
                               cout << "  radius: " << radius << endl;}
};

class Rectangle : public Shape
{
private:
    double height;
    double width;

public:
    Rectangle (){height = 1; width = 1;}
    Rectangle (double h, double w):height(h), width(w){}
    Rectangle (double x, double y, double h, double w):Shape(x, y), height(h), width(w){}
    void area () override {cout << "Rectangle area: " << height * width << endl;}
    void perimeter () override {cout << "Rectangle perimeter: " << 2 * (height + width) << endl;}
    void showInfo (){cout << "Rectangle x: " << x << endl;\
                     cout << "          y: " << y << endl;\
                     cout << "     height: " << height << endl;\
                     cout << "      width: " << width << endl;}
};

int main()
{
    Circle c1(1, 1, 2);
    c1.area();
    c1.perimeter();
    c1.showInfo();
    cout << endl;

    Rectangle r1(1, 1, 2, 1);
    r1.area();
    r1.perimeter();
    r1.showInfo();

    return 0;
}
