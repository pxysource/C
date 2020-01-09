/**********************************************************
 * 编写一个程序，将用户输入的包含任意字母的字符串其中的字母大小写翻转
 * ********************************************************/

#include <iostream>
using namespace std;

int main()
{
    string str;
    unsigned int i = 0;
    cin >> str;
    cout << "before: " << str <<endl;

    for (i = 0; i < str.length (); i++)
    {
        //方法一：
        /*
        if (isupper (str[i]))
        {
            str[i] = tolower (str[i]);
        }
        else if(islower (str[i]))
        {
            str[i] = toupper (str[i]);
        }
        */

        //方法二：'a'-'A'=0x20
        if (str[i] >= 'A' && str[i] <= 'Z' && (str[i] |= 0x20));
        else if (str[i] >= 'a' && str[i] <= 'z' && (str[i] &= ~0x20));
        else;
    }

    cout << "after:  " << str << endl;

    return 0;
}
