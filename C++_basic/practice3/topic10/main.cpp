#include <iostream>
using namespace std;

class OAA
{
public:
    OAA (){cout << "OAA" << endl;}
};

class School
{
private:
    unsigned int _classes;
    OAA _myOaa;
public:
    School (){cout << "School" << endl;}
    void termBegin (){}

};

class Board
{
public:
    Board (){cout << "Board" << endl;}
};

class Company
{
private:
    double _profitRate;
    Board _myBoard;
public:
    Company (){cout << "Compant" << endl;}
    void paytaxes (){}

};

class trainingAgency : public School, public Company
{
public:
    trainingAgency (){cout << "trainingAgency" << endl;}
};

int main()
{
    trainingAgency gec;

    return 0;
}
