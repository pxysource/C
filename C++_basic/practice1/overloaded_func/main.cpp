/*************************************************************
 *8.编写一个函数 calculate()，利用C++的函数重载技术，实现它两个功能各异的版本：（函数重载）
 *第一个版本，如果传过去两个数字，则返回他们的总和。
 *第二个版本，如果传过去一个C语言风格的字符串，则返回字串的长度
 * ***********************************************************/
#include <iostream>
#include <cstring>
using namespace std;

int calculate (int a, int b);

int calculate (char *str);

int calculate (int a, int b)
{
    return a + b;
}

int calculate(const char *str)
{
    return strlen (str);
}

int main (void)
{
    int a = 1;
    int b = 2;
    const char *str = "Hello World";

    cout << "a + b = " << calculate (a,b) <<endl;
    cout << "str lenght: " << calculate (str) <<endl;

    return 0;
}
