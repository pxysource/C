#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0;

    cout << "Please input an integer (range > 0): " << endl;
    cin >> n;

    list<int> l;
    list<int> tmp;
    for (int i = 1; i <= n; i++)
    {
        l.push_back(i);
    }

    l.sort();
    std::for_each(l.begin(), l.end(), [](int item){cout << item << "\t";});
    cout << endl;

    for (list<int>::iterator it = l.begin(); it != l.end(); it++)
    {
        if (0 != (*it % 2))
        {
            tmp.push_back(*it);
        }
    }

    for (list<int>::reverse_iterator it = l.rbegin(); it != l.rend(); it++)
    {
        if (0 == (*it % 2))
        {
            tmp.push_back(*it);
        }
    }

    l.clear();
    l = tmp;
    std::for_each(l.begin(), l.end(), [](int item){cout << item << "\t";});
    cout << endl;

    return 0;
}
