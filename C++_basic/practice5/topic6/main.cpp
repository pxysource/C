#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v1;
    auto print = [](const int &a){cout << a << " ";};

    std::srand(time(nullptr));
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(std::rand()%100);
    }

    for_each(v1.begin(), v1.end(), print);
    cout << endl;

    int n = 0;
    for_each(v1.begin(), v1.end(), [&n](const int &a){n += (0 == (a % 3));});
    cout << n << endl;

    return 0;
}
