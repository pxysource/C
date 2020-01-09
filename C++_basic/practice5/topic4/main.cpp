#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    typedef std::multimap<string, string> MapAddrBook;
    typedef pair<const string, string> Pair;

    MapAddrBook ab1;
    MapAddrBook::iterator it;
    ab1.insert(Pair("zhangshan", "15228935997"));
    ab1.insert(Pair("zhangshan", ""));
    ab1.insert(Pair("zhangshan", "13118040006"));
    ab1.insert(Pair("lisi", "13199887755"));
    ab1.insert(Pair("lisi", "13566676878"));
    ab1.insert(Pair("jack", "18547465656"));
    ab1.insert(Pair("rose", "19650066757"));
    ab1.insert(Pair("bill", "14455675676"));
    ab1.insert(Pair("bill", "15804045065"));
    ab1.insert(Pair("bill", ""));

    for (it = ab1.begin(); it != ab1.end(); it++)
    {
        cout << (*it).first << " phone number number:";
        cout << ab1.count((*it).first) << endl;
    }
    cout << endl;

    for (it = ab1.begin(); it != ab1.end(); it++)
    {
        cout << (*it).first << " : " << (*it).second << endl;
    }
    cout << endl;

    pair<MapAddrBook::iterator, MapAddrBook::iterator> range =
            ab1.equal_range("zhangshan");
    for (it = range.first; it != range.second; it++)
    {
        cout << (*it).first << " : " << (*it).second << endl;
    }

    return 0;
}
