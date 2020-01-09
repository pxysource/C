#include <iostream>
#include "stack.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<typename T1, typename T2>
void decToAny(T1 dec, T2 system, string & rt)
{
    cout << "Warning: Please notice both param1 "
            "and param2 are int(integer) type!" << endl;
    rt = "nothing";
}

//函数模板要想具体化也就是全特化,但是函数声明中没有用到模板
//也就是说与普通非模板函数的声明一样
//则必须要有通用的版本来说明这是个模板函数
template<>
void decToAny(unsigned int dec, unsigned int system, string & rt)
{
    if (system < 2 || system > 16)
    {
        cout << "Please input system(rang [2, 16])." << endl;
        return;
    }

    unsigned int tmp = 0;
    Stack<unsigned int> s;

    do
    {
        tmp = dec % system;
        s.push(tmp);
        dec /= system;
    }while(dec > 0);

    //'0' == 48
    while(!s.isEmpty())
    {
        tmp = s.pop();
        rt.push_back((tmp > 9) ? (tmp + 'a' - 10) : (tmp + 48));
    }
}

int main()
{
    string result;
    unsigned int dec_num;
    unsigned int sys_num;

    cout << "Please input decimal number to convert: ";
    cin >> dec_num;
    cout << "Please input system number(range [2,16]): ";
    cin >> sys_num;
    decToAny(dec_num, sys_num, result);
    cout << result << endl;

    return 0;
}
