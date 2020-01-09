#include <iostream>
using namespace std;

class Part1
{
public:
    Part1 (){cout << "Part1" << endl;}
    ~Part1 (){cout << "~Part1" << endl;}

};

class Part2
{
public:
    Part2 (){cout << "Part2" << endl;}
    ~Part2 (){cout << "~Part2" << endl;}

};

class Whole
{
private:
    Part1 p1;
    Part2 p2;

public:
    Whole (){cout << "Whole" << endl;}
    ~Whole (){cout << "~Whole" << endl;}
};

int main()
{
    Whole w1;

    return 0;
}
