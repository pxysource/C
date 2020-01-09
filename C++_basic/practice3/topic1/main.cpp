#include <iostream>
using namespace std;

class card
{
private:
    const string _company;
    const string _account;
    const string _cardNo;

public:
    card ();
    card (const string co, const string ac, const string cn)\
                               :_company(co), _account(ac), _cardNo(cn)\
                               {cout << "card constructor called" << endl;}
    virtual void enquiry ()=0;
    virtual void deposit (double moneyNo)=0;
    virtual void withdraw (double moneyNo)=0;
    string company () const{return _company;}
    string account () const{return _account;}
    string cardNo () const{return _cardNo;}
};

class cashCard : public card
{
private:
    double _balance;

public:
    cashCard (const string co, const string ac,\
              const string cn, double ba=0):card(co, ac, cn)\
             {_balance = ba;}
    double balance (){return _balance;}
    virtual void enquiry () override{cout << "company: " << company() << endl;\
                                     cout << "account: " << account() << endl;\
                                     cout << "card number: " << cardNo() << endl;\
                                     cout << "balance: " << balance() << endl;}

    virtual void deposit (double moneyNo) override;
    virtual void withdraw (double moneyNo) override;
};

void cashCard::deposit(double moneyNo)
{
    if (moneyNo < 0)
    {
        cout << "Error: cashCard deposit error!" << endl;
    }
    else
    {
        _balance += moneyNo;
        cout << "cashCard deposit: " << "$" << moneyNo << endl;
    }
}

void cashCard::withdraw (double moneyNo)
{
    if (moneyNo < 0)
    {
        cout << "Error: cashCard withdraw error!" << endl;
    }
    else if (moneyNo > _balance)
    {
        cout << "Error: cashCard balance only: " << "$" << _balance << endl;
    }
    else
    {
        _balance -= moneyNo;
        cout << "cashCard withdraw: " << "$" << moneyNo << endl;
    }
}

class creditCard : public card
{
private:
    double _limit;
    double _interestRate;
    double _debt;

public:
    creditCard (const string co, const string ac, const string cn,\
                double li=1000, double in=0.1, double de=0):card(co, ac, cn)\
                {_limit= li; _interestRate = in; _debt = de;}
    virtual void enquiry () override{cout << "company: " << company() << endl;\
                                     cout << "account: " << account() << endl;\
                                     cout << "card number: " << cardNo() << endl;\
                                     cout << "limit: " << _limit << endl;\
                                     cout << "interestRate: " << _interestRate << endl;\
                                     cout << "debt: " << _debt << endl;}
    virtual void deposit (double moneyNo) override;
    virtual void withdraw (double moneyNo) override;
    void setLimit (double in){_interestRate = in; cout << "setlimit: " << in << endl;}
};

void creditCard::deposit (double moneyNo)
{
    if (moneyNo < 0)
    {
        cout << "Error: creditCard deposit error!" << endl;
    }
    else
    {
        _debt -= moneyNo;
        cout << "cashCard deposit: " << "$" << moneyNo << endl;
    }
}

void creditCard::withdraw (double moneyNo)
{
    if (moneyNo < 0)
    {
        cout << "Error: creditCard withdraw error!" << endl;
    }
    else if ((moneyNo + moneyNo * _interestRate + _debt) > _limit)
    {
        cout << "Error: creditCard limit only: " << "$" << _limit << endl;
    }
    else
    {
        _debt = moneyNo + moneyNo * _interestRate ;
        cout << "creditCard withdraw " << "$" << moneyNo << endl;
    }
}

int main ()
{
    {
        cashCard c1("xxxx", "1234", "623989239", 200);
        c1.enquiry();
        c1.deposit(100);
        c1.enquiry();
        c1.withdraw(400);
        c1.enquiry();
    }

    cout << endl;

    {
        creditCard c2("yyyy", "5678", "6747803403403");
        c2.enquiry();
        c2.withdraw(950);
        c2.enquiry();
        c2.deposit(100);
        c2.enquiry();
    }

    return 0;
}
