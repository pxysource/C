#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
    string str;
    Stack<string> s1;

    while ((cin >> str) && !("0" == str))
    {
        s1.push(str);
    }

    cout << endl;

    while (!s1.isEmpty())
    {
        cout << s1.pop() << endl;
    }

    return 0;
}
