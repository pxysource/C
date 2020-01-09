#include "product.h"

double product::_totalAmount = 0.0;
double Apple::_totalSoldWeight = 0.0;
int Shampoo::_totalSoldCount = 0;

product::product(double costValue, double priceValue, double discountValue)
{
    _cost = costValue;
    _price = priceValue;
    _discount = discountValue;
}

void Apple::sold(int soldWeight, double extraDiscount)
{
    double oldPrice = this->price() * (1 - this->discount());
    double newAmount = oldPrice * soldWeight * (1 - extraDiscount);

    this->_totalAmount += newAmount;
    this->_totalSoldWeight += soldWeight;
}

void Shampoo::sold(int soldCount, double extraDiscount)
{
    double oldPrice = this->price() * (1 - this->discount());
    double newAmount = oldPrice * soldCount * (1 - extraDiscount);

    this->_totalAmount += newAmount;
    this->_totalSoldCount += soldCount;
}
