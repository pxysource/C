#include <iostream>
using namespace std;

class Car
{
private:
    double mass;
    double maxSpeed;

public:
    Car (){cout << "Car" << endl;}
    ~Car (){cout << "~Car" << endl;}
    void move ();
    void maintain ();
};

class ElectroMobile : public Car
{
private:
    double electricQuantity;

public:
    ElectroMobile (){cout << "ElectroMobile" << endl;}
    ~ElectroMobile (){cout << "~ElectroMobile" << endl;}
    void charge ();
};

class AeroCar : public Car
{
public:
    AeroCar (){cout << "AeroCar" << endl;}
    ~AeroCar (){cout << "~AeroCar" << endl;}
    void fly ();
};

class StatellitePhone
{
private:
    string addressbook;

public:
    StatellitePhone (){cout << "SatellitePhone" << endl;}
    ~StatellitePhone (){cout << "~SatellitePhone" << endl;}
    void call ();
};

class MotorHomes : public Car
{
private:
    int beds;
    StatellitePhone satellitePhone;
public:
    MotorHomes (){cout << "MotorHomes" << endl;}
    ~MotorHomes (){cout << "~MotorHomes" << endl;}
    void camping ();
    void cooking ();
};

int main()
{
    Car mycar;
    cout << endl;
    ElectroMobile myelct;
    cout << endl;
    AeroCar myaero;
    cout << endl;
    MotorHomes mymoto;
    cout << endl;

    return 0;
}
