/****************************************************
 *5.编写一个函数，在不使用指针的情况下，交换两个字符串的内容
 * **************************************************/
#include <iostream>
using namespace std;

void myswap (string &str1, string &str2)
{
    string tmp;
    tmp = str1;
    str1 = str2;
    str2 = tmp;
}

int main ()
{
    string mystr1;
    string mystr2;

    cout << "Please input two strings: " <<endl;
    cin >> mystr1 >> mystr2;
    cout << "before: " << mystr1 << " " << mystr2 << endl;
    myswap(mystr1, mystr2);
    cout << "after : " << mystr1 << " " << mystr2 << endl;

    return 0;
}
