#include <iostream>
#include "kitty.h"

using namespace std;

int main()
{
    Kitty myCat ('m', Kitty::BLACK, 1.0);
    myCat.info ();
    cout << endl;

    Kitty yourCat;
    yourCat.info ();

    return 0;
}
