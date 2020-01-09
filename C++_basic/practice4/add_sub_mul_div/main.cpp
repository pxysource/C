#include <iostream>
#include "stack.h"

using std::cin;
using std::cout;
using std::string;

inline bool isOperator(const char ch)
{
    return (('*' == ch) ||
            ('/' == ch) ||
            ('+' == ch) ||
            ('-' == ch));
}

inline bool isData(const char ch)
{
    return (ch >= '0' && ch <= '9');
}

bool exp_check(string & s)
{
    if (s.empty())
    {
        cout << "Expresion is empty!" << endl;
        return false;
    }
    else if (!isData(*s.begin()))
    {
        cout << "Expresion format error!" << endl;
        return false;
    }

    //用于判断是否有符号相邻
    int count = 0;
    string::iterator it = s.begin();

    while (it != s.end())
    {
        if (isOperator(*it))
            count++;
        else if (isData(*it))
        {
            if (count >= 2)
            {
                cout << "Expression format error!" << endl;
                return false;
            }
            count = 0;
        }
        else
        {
            cout << "Expression format error!" << endl;
            return false;
        }

        it++;
    }

    //最后一个字符不是数字
    if (!isData(*--it))
    {
        cout << "Expression format error!" << endl;
        return false;
    }

    return true;
}

template<typename T>
T compute(string & exp)
{
    if (!exp_check(exp))
        return T(0);

    T tmp;
    char charopt;
    const char *ptr = exp.c_str();
    memset(&tmp, 0, sizeof(tmp));

    Stack<char> opt;
    Stack<T> item;

    while('\0' != *ptr)
    {
        if (isData(*ptr))
        {
            tmp = atoi (ptr);

            //'-'的处理
            if (!opt.isEmpty() && '-' == opt.top())
            {
                tmp = -tmp;
                opt.pop();
                opt.push('+');
            }

            item.push(tmp);

            while(isData(*ptr))
            {
                ptr++;
                continue;
            }
        }

        if ((!opt.isEmpty() && (charopt = opt.top())) &&
                ('*' == charopt || '/' == charopt))
        {
            charopt = opt.pop();
            T right = item.pop();
            T left = item.pop();
            T result = (charopt == '*') ? (left * right) : (left / right);

            item.push(result);
        }

        if (isOperator(*ptr))
            opt.push(*ptr);
        ptr++;
    }

    while (!opt.isEmpty())
    {
        charopt = opt.pop();
        T right = item.pop();
        T left = item.pop();
        T result = charopt == '+' ? (left + right) : (left - right);

        item.push(result);
    }

    return item.pop();
}

int main()
{
    string str;
    cout << "Please input a expression:";
    cin >> str;

    cout << compute<int>(str) << endl;

    return 0;
}
