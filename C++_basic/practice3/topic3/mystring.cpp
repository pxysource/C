#include "mystring.h"

MyString::MyString(const char *cstr)
{
    int len = strlen(cstr);
    _str = new char[100];
    memcpy (_str, cstr, len + 1);
    cout << "constructor called." << endl;
}

MyString::~MyString()
{
    delete [] _str;
    cout << "deconstructor called." << endl;
}

MyString::MyString(const MyString &r)
{
    if (this == &r)
    {
        return;
    }

    int len = strlen(r._str);
    this->_str = new char[100];
    memcpy(this->_str, r._str, len + 1);
    cout << "copy constructor called." << endl;
}

MyString &MyString::operator=(const MyString &r)
{
    cout << "operator=() called." << endl;
    if (this == &r)
    {
        return *this;
    }

    int len = strlen(r._str);
    memcpy(this->_str, r._str, len + 1);
    return *this;
}
