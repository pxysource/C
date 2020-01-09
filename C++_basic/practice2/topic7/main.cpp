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
    virtual void fly (){cout << "copter fly" << endl;}
};

class Bomber : public airCraft
{
public:
    virtual void refuel(){cout << "Bomber" << endl;}
    virtual void fly (){cout << "Bomber fly" << endl;}
};

class Pilot
{
public:
    void pilot (airCraft &a);
};

void Pilot::pilot (airCraft &a)
{
    a.refuel();
    a.fly();
}

int main()
{
    Pilot p1;

    Copter c1;
    Bomber b1;

    airCraft &a1 = c1;
    p1.pilot (a1);
    cout << endl;

    airCraft &a2 = b1;
    p1.pilot (a2);

    return 0;
}
