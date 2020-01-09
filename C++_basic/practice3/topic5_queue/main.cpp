#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
    char ch = 'a';
    Queue<char> q1;

    for (int i = 0; i < 10; i++)
    {
        q1.inQueue(ch++);
        cout << q1.endValue() << "\t";
    }

    cout << endl;

    while (!q1.isEmpty())
    {
        cout << q1.outQueue() << "\t";
    }

    cout << endl;

    return 0;
}
