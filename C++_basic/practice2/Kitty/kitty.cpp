#include "kitty.h"

using std::cout;
using std::endl;

Kitty::Kitty ()
{
    _weight = 1;
    _color  = BLACK;
    _gender = 'm';

    cout << "generate a 1kg black male cat" << endl;
}

Kitty::Kitty (char gender, enum CAT_COLOR color, double weight)
{
    _weight = weight;
    _color  = color;
    _gender = gender;

    cout << "generate a " << _weight << "kg "
         << _color << " "
         << _gender << " cat" << endl;
}

Kitty::~Kitty ()
{
    cout << "a cat fade away" << endl;
}

void Kitty::eat()
{
    _weight++;
    if (_weight > 5)
    {
        cout << "I'm too fat." << endl;
    }
}

void Kitty::sleep()
{
    cout << "zzzzzZZZZZZZZZZ" << endl;
}

void Kitty::actingCute()
{
    cout << "~~~~~~~~~~~~~~~" << endl;
}

void Kitty::info()
{
    cout << "weight = " << _weight << endl;
    cout << "gender = " << _gender << endl;
    cout << "color  = " << _color << endl;
}
