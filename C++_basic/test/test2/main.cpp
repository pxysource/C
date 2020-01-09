#include <iostream>
#include <vector>
using namespace std;


class A
{
    int _count;
public:
    A(int i){_count = i;cout << _count << "default construction called" << endl;}
    A(const A &r){cout << r._count << " " << __LINE__ << '\n' << endl;}
    A(const A &&r){cout << __LINE__ << endl;}
};

int main()
{
    vector<A> v1;
    vector<A> v2;
    A a(1);
    A b(2);
    A c(a);

    cout << "1th: ";
    v1.push_back(a);
    cout << "2th: ";
    v1.push_back(b);
    cout << "3th: ";
    v1.push_back(a);
    //v1.push_back(b);
    //v1.push_back(std::move(a));
    //v1.push_back(std::move(b));

    cout << "Hello World!" << endl;
    return 0;
}
