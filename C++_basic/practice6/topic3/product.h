#ifndef PRODUCT_H
#define PRODUCT_H

class product
{
protected:
    static double _totalAmount;
    double _cost;
    double _price;
    double _discount;
public:
    product(double costValue=0.0, double priceValue=0.0, double discountValue=0.0);
    double cost()const{return _cost;}
    double price()const{return _price;}
    double discount()const{return _discount;}

    void setCost(double costValue){_cost = costValue;}
    void setPrice(double priceValue){_price = priceValue;}
    void setDiscount(double discountValue){_discount = discountValue;}
    static double totalAmount(){return _totalAmount;}

    virtual void sold(int quantity, double extraDiscount)=0;
};

class Apple : public product
{
private:
    static double _totalSoldWeight;

public:
    Apple(double costValue, double priceValue, double discountValue)
        :product(costValue, priceValue, discountValue){}
    virtual void sold(int soldWeight, double extraDiscount);
    static double totalWeight(){return _totalSoldWeight;}
};

class Shampoo : public product
{
private:
    static int _totalSoldCount;
public:
    Shampoo(double costValue, double priceValue, double discountValue)
        :product(costValue, priceValue, discountValue){}
    virtual void sold(int soldCount, double extraDiscount);
    static int totalSoldCount(){return _totalSoldCount;}
};

#endif // PRODUCT_H
