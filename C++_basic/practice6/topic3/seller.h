#ifndef SELLER_H
#define SELLER_H

#include "product.h"
#include <exception>
#include <stdexcept>

using namespace std;

class Excp : public std::invalid_argument
{
private:
    const string _name;
    string _msg;
public:
    Excp(const string nameValue=0, const string msg=0):invalid_argument(msg),
        _name(nameValue){}
    string whathappen(){_msg.append(_name);
                        _msg.append(" : ");
                        _msg.append(what()); return _msg;}
};

class seller
{
private:
    const string _name;
    double _totalCost;
    double _totalAmount;
    double _profitRate;

    void updateProfitrate(){_profitRate = (_totalAmount - _totalCost) / _totalCost;}
public:
    seller(const string sellerName=0, double totalcost=0.0,
           double totalamount=0.0, double profitrate=0.0)
        : _name(sellerName),
          _totalCost(totalcost),
         _totalAmount(totalamount),
         _profitRate(profitrate){}

    const string name(){return _name;}
    void soldGoods(product &rhs, int quantity, double extraDiscount);
    double profitRate(){return _profitRate;}
};

#endif // SELLER_H
