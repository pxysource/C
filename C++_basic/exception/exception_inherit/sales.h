#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <stdexcept>

class Sales
{
public:
    enum {MONTHS=12};

    class bad_index : public std::logic_error
    {
    private:
        int bi;//bad index value
    public:
        explicit  bad_index(int ix,
            const string & s="Index error in Sales object\n");
        int bi_value() const {return bi;}
        ~bad_index();//???????????????
    };

    explicit Sales(int yy=0);
    Sales(int yy, const double *gr, int n);
    int Year() const {return year;}


private:
    double gross[MONTHS];
    int year;
};

class LabeledSales : public Sales
{
public:
    class nbad_index : public Sales::bad_index
    {
    private:
        std::string lbl;
    public:
        nbad_index(const std::string & lb, int ix,
            const std::string & s="Index error in LabeledSales object\n");
    };

    explicit LabeledSales(const std::string & lb="none", int yy);
    LabeledSales(const std::string &lb, int yy, const double *gr, int n);
    const std::string & Lable() const {return lable;}

}

#endif // SALES_H
