#include <iostream>
using namespace std;

class Demo
{
private:
    int a;
public:
    //explicit:显示声明,不接受单参数赋值
    explicit Demo(int a){this->a = a;}
};

int main()
{
    Demo d1(1);

    Demo d2 = d1; // 使用相同的类对象d1来初始化d2

    Demo d3 = 88; // 使用整型常量来初始化d3

    return 0;
}


