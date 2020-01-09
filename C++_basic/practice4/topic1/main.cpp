#include <iostream>
using namespace std;

//用模板的时候, 如果函数模板有多个不同类型的参数
//1.如何声明中间变量的类型?
//2.如何得到返回值类型?
template<typename T1, typename T2>
auto maxValue (T1 t1, T2 t2)->decltype(t1 > t2 ? t1 : t2)
{
    return t1 > t2 ? t1 : t2;
}

int main()
{
    cout << "max: "  << maxValue('a', 2) << endl;

    return 0;
}
