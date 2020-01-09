#include <iostream>
using namespace std;

class airCraft
{
public:
    virtual void refuel (){cout << "universal" <<endl;}
    virtual void fly ()=0;
};

class Copter : public airCraft
{
public:
    void fly () override {cout << "copter fly" << endl;}
};

class Bomber : public airCraft
{
public:
    void refuel() override {cout << "Bomber" << endl;}
    void fly () override {cout << "Bomber fly" << endl;}

};

int main()
{
    Copter c1;
    c1.refuel();
    c1.fly();
    cout << endl;

    Bomber b1;
    b1.refuel();
    b1.fly();

    return 0;
}
