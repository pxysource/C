/************************************************************
 *6.编写一个程序，去掉给定字符串中重复的字符。例如将google转化为gole
 * **********************************************************/
#include <iostream>
using namespace std;

int main ()
{
    string src_str = "google";
    unsigned int i = 0;
    unsigned int j = 0;

    cout << src_str << endl;

    for (i = 0; i < src_str.length(); i++)
    {
        for (j = i + 1; j < src_str.length(); j++)
        {
            if (src_str[i] == src_str[j])
            {
                src_str.erase(j, 1);
            }
        }
    }

    cout << src_str << endl;

    return 0;
}
