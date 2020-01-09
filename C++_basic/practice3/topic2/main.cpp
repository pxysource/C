#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Commodity
{
private:
    double _cost;
    double _price;

public:
    Commodity (double cost=0.0, double price=0.0):_cost(cost), _price(price)
    {cout << "Commodity constructor called" << endl;}
    double cost (){return _cost;}
    double price (){return _price;}
    virtual double sold ()=0;
};

class Apple : public Commodity
{
private:
    static double _kg;

public:
    Apple (){/*cout << "Apple default constructor called" << endl;*/}
    Apple (double co, double pr, double kilogram):Commodity(co, pr){_kg = kilogram;
                                                                    //cout << "Apple constructor called" << endl;
                                                                   }
    virtual double sold (){return _kg * price();}
    static double kg (){return _kg;}
};

double Apple::_kg = 0;

class Shampoo : public Commodity
{
private:
    static int _bottle;
public:
    Shampoo (){/*cout << "Shampoo default constructor called" <<  endl;*/}
    Shampoo (double co, double pr, double bo):Commodity(co, pr){_bottle = bo;
                                                                    //cout << "Shampoo constructor called" << endl;
                                                                   }
    virtual double sold (){return _bottle * price();}
    static int bottle (){return _bottle;}
};

int Shampoo::_bottle = 0;

class Seller
{
private:
    double _totalAmount;
    double _profit;
    double _count;
    double _discount;
    static double _total;
    Apple a1;
    Shampoo s1;

public:
    Seller (Apple &a, Shampoo &s, double di=1);
    void totalAmount (){_totalAmount = (a1.sold() + s1.sold()) * _discount;
                        _total += _totalAmount;
                       }
    void profit (){	double costTotal;
                    costTotal = a1.cost() * a1.kg() + s1.cost() * s1.bottle();
                    _profit = _totalAmount - costTotal;
                  }
    void count (){_count = _profit / _totalAmount;}
    void showInfo (){
                    cout << std::fixed << std::setprecision(2);
                    cout << _totalAmount << "\t\t";
                    cout << _profit << '\t';
                    cout << _count << '\t';
                    cout << _discount << endl;
                    }
    static void showTotal (){cout << "store total Amount: " << _total << endl;}
    void discount (double di=1);
};

double Seller::_total = 0;

Seller::Seller (Apple &a, Shampoo &s, double di)
{
    a1 = a;
    s1 = s;
    _totalAmount = 0;
    _profit = 0;
    _count = 0;

    if (di < 0 || di > 1)
    {
        cout << "Error: discount error! Do not discount!"  << endl;
        _discount = 1;
    }
    else
    {
        _discount = di;
    }
}

void Seller::discount(double di)
{
    if (di < 0 || di > 1)
    {
        cout << "Error: discount error! Do not discount!"  << endl;
        _discount = 1;
    }
    else
    {
        _discount = di;
    }
}

int main()
{
    cout << "Seller\t" << "totalAmount\t" << "profit\t" << "count\t" << "discount" << endl;
    {
        cout << "Jack\t";
        Apple ap1(2, 4, 10);
        Shampoo sh1(20, 30, 20);
        Seller Jack(ap1, sh1);
        Jack.totalAmount();
        Jack.profit();
        Jack.count();
        Jack.showInfo();
    }

    {
        cout << "Rose\t";
        Apple ap2(2, 5, 20);
        Shampoo sh2(20, 25, 10);
        Seller Rose(ap2, sh2, 0.7);
        Rose.totalAmount();
        Rose.profit();
        Rose.count();
        Rose.showInfo();
    }

    {
        cout << "Bill\t";
        Apple ap3(2, 4, 15);
        Shampoo sh3(20, 30, 20);
        Seller Bill(ap3, sh3, 0.8);
        Bill.totalAmount();
        Bill.profit();
        Bill.count();
        Bill.showInfo();
    }
    cout << endl;
    Seller::showTotal();

    return 0;
}
