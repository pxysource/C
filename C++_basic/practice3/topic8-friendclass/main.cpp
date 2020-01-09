#include <iostream>
#include "tv.h"
#include "remote.h"
using namespace std;

int main()
{
    TV tcl;
    tcl.showChannel();
    tcl.showVolume();
    tcl.setChannel(0);
    tcl.setVolume(0);
    tcl.showChannel();
    tcl.showVolume();

    Remote r1;
    r1.addorIncChannel(tcl, 1);
    r1.addorIncVolume(tcl, 1);
    tcl.showChannel();
    tcl.showVolume();

    r1.selectChannel(tcl, 45);
    r1.selectVolume(tcl, 45);
    tcl.showChannel();
    tcl.showVolume();

    return 0;
}
