#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::auto_ptr;
using std::unique_ptr;
using std::shared_ptr;

unique_ptr<string> test(void)
{
    unique_ptr<string> tmp(new string("world"));
    return tmp;
}

int main()
{
    {
        unique_ptr<int []> ptr(new int[10]);
        shared_ptr<int []> ptr3(new int[10]);
        unique_ptr<string> ptr2;
        ptr2 = test();
        //cout << *ptr << endl;
        cout << *ptr2 << endl;
    }

    return 0;
}
