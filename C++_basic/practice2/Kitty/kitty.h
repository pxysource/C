#ifndef KITTY_H
#define KITTY_H

#include <iostream>

class Kitty
{
public:
    enum CAT_COLOR{BLACK, WHITE, BLUE, BROWN};

private:
    float _weight;
    char  _gender;
    enum CAT_COLOR _color;

public:
    Kitty ();
    Kitty (char gender, enum CAT_COLOR color, double weight);
    ~Kitty ();
    void eat ();
    void sleep ();
    void actingCute ();
    void info ();
};

#endif // KITTY_H
