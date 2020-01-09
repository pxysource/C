#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(const double &a, const double &b)
{
    return (a > b);
}

class Comp
{
public:

    bool operator()(const double &a, const double &b){return (a > b);}
};

void show(const double &a)
{
    cout << a << " ";
}

class Show
{
public:

    void operator()(const double &a){cout << a << " ";}
};


int main()
{
    vector<double> v1;

    std::srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        v1.push_back((static_cast<double>(std::rand() % 100)) / 10);
    }

    std::for_each(v1.begin(), v1.end(), Show());
    cout << endl;

    vector<double>::iterator it;
    std::sort(v1.rbegin(), v1.rend(), Comp());

    std::for_each(v1.begin(), v1.end(), show);
    cout << endl;

    return 0;
}
