#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

void arrayUse()
{
    array<int, 5> arr1 = {1, 3, 2, 5, 4};

    for (array<int, 5>::iterator it = arr1.begin(); it < arr1.end(); it++)
    {
        cout << *it << "\t";
    }
    cout << endl;

    std::sort(arr1.begin(), arr1.end());
    for (array<int, 5>::iterator it = arr1.begin(); it < arr1.end(); it++)
    {
        cout << *it << "\t";
    }

    cout << endl;
}

void vectorUse()
{
    //要用初始化, 不能写上长度
    //vector<int> arr3(10);
    vector<int> arr1 = {1, 2, 3};
    //vector<int> arr2;

    std::srand(time(nullptr));

    cout << "? empty: " << arr1.empty() << endl;

    for (int i = 0; i < 10; i++)
    {
        arr1.push_back(std::rand() % 100);
    }

    for(vector<int>::iterator it = arr1.begin(); it < arr1.end(); it++)
    {
        cout << *it << "\t";
    }
    cout << endl;

    std::sort(arr1.rbegin(), arr1.rend());
    for(vector<int>::iterator it = arr1.begin(); it < arr1.end(); it++)
    {
       cout << *it << "\t";
    }
    cout << endl;

    std::for_each(arr1.begin(), arr1.end(), [](int item){cout << item << "\t";});
    cout << endl;
}

void setUse()
{
    const int size = 6;
    string s1[size] = {"buffoon", "thinkers", "for", "heavy", "can", "for"};
    set<string> a(s1, s1 + size);
    ostream_iterator<string, char> out(cout, " ");
    std::copy(a.begin(), a.end(), out);
    cout << endl;
}

void multimapUse()
{
    typedef int KeyType;
    typedef std::pair<const KeyType, string> Pair;
    typedef std::multimap<KeyType, string> MapCode;

    MapCode codes;
    codes.insert(Pair(415, "San Francisco"));
    codes.insert(Pair(510, "Oakland"));
    codes.insert(Pair(718, "Branklyn"));
    codes.insert(Pair(718, "Staten Island"));
    codes.insert(Pair(415, "San Rafael"));
    codes.insert(Pair(510, "Berkeley"));

    cout << "Number of cities with area code 415: " << codes.count(415) << endl;
    cout << "Number of cities with area code 718: " << codes.count(415) << endl;
    cout << "Number of cities with area code 510: " << codes.count(415) << endl;

    cout << "Area code\t" << "City" << endl;
    MapCode::iterator it;
    for (it = codes.begin(); it != codes.end(); it++)
    {
        cout << (*it).first << "\t\t" << (*it).second << endl;
    }

    pair<MapCode::iterator, MapCode::iterator> range = codes.equal_range(718);
    for (it = range.first; it != range.second; it++)
    {
        cout << (*it).second << endl;
    }
}

int main()
{
    //arrayUse();

    //vectorUse();

    //setUse();

    multimapUse();
    return 0;
}
