#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

class MyString
{
private:
    char *_str;
public:
    //单参数构造函数，禁用直接赋值基本类型
    //如MyString s5 = "abcd";将被禁止
    explicit MyString (const char *cstr="");
    ~MyString ();
    MyString (const MyString &r);
    MyString &operator= (const MyString &r);
    void output (){cout << _str << endl;}
};

#endif // MYSTRING_H
