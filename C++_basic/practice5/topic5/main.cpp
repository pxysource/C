#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class Compare
{
private:
    bool _flag;
public:
    Compare(bool flag=true):_flag(flag){}
    bool operator()(const T &a, const T &b){return _flag ? (a < b) : (a > b);}
};

int main()
{
    int i = 0;
    vector<int> v1;
    auto print = [](const int a){cout << a << " ";};

    cout << "Please input some integer (a char to exit): " << endl;
    while (1)
    {
        cin >> i;
        try{
            if (cin.fail())
            {
                throw runtime_error("error");
            }
          }
        catch(runtime_error &e)
                 { cout << "cin exception" << endl;
                   cin.clear();
                   cin.sync();
                   break;
                 };
        v1.push_back(i);
    }

    std::for_each(v1.begin(), v1.end(), print);
    cout << endl;

    std::sort(v1.begin(), v1.end(), Compare<int>());

    std::for_each(v1.begin(), v1.end(), print);
    cout << endl;

    std::sort(v1.begin(), v1.end(), Compare<int>(false));

    std::for_each(v1.begin(), v1.end(), print);
    cout << endl;

    return 0;
}
