#include "seller.h"

void seller::soldGoods(product &rhs, int quantity, double extraDiscount)
{
    double cost = rhs.cost();
    double newPrice = rhs.price() * (1 - rhs.discount()) * (1 - extraDiscount);
    if (newPrice < cost)
    {
        throw Excp(this->_name, "discount error");
    }

    _totalCost += (quantity * rhs.cost());

    double amount = quantity * rhs.price() * (1 - rhs.discount()) * (1 - extraDiscount);
    _totalAmount += amount;

    updateProfitrate();
    rhs.sold(quantity, extraDiscount);
}
