#include <iostream>
#include "max.h"

void print(int a, int b);

int main()
{
    using std::cout;
    using std::endl;
    print(1, 2);

    cout << "max(a, b)" << max(1, 2) << endl;
    return 0;
}


