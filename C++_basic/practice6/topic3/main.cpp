#include <iostream>
#include "seller.h"
#include "product.h"
using namespace std;

int main()
{
    Shampoo Rejoice(15, 30, 0.1);

    seller *Jack = new seller("Jack");
    seller *Rose = new seller("Rose");
    seller *Bill = new seller("Bill");

    try
    {
        Jack->soldGoods(Rejoice, 5, 0.0);
        Rose->soldGoods(Rejoice, 12, 0.03);
        Bill->soldGoods(Rejoice, 100, 0.1);

        Shampoo HeadAndShoulders(35, 60, 0.0);
        Jack->soldGoods(HeadAndShoulders, 20, 0.0);


        cout << "洗发水总销售额：" << Rejoice.totalAmount() << endl;

        cout << "Jack的利润率：" << Jack->profitRate() << endl;
        cout << "Rose的利润率：" << Rose->profitRate() << endl;
        cout << "Bill的利润率：" << Bill->profitRate() << endl;


        Apple Fuji(2.8, 5, 0);
        Rose->soldGoods(Fuji, 1000, 9.9);
    }
    catch(Excp &e){cout << e.whathappen() << endl;}

    cout << "Jack的利润率：" << Jack->profitRate() << endl;
    cout << "Rose的利润率：" << Rose->profitRate() << endl;
    cout << "Bill的利润率：" << Bill->profitRate() << endl;

    return 0;
}
