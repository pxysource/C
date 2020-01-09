#include <iostream>
#include <array>
#include <cstring>
using namespace std;

template<typename T>
T maxn(T arr[], int size)
{
    T max;
    max = arr[0];

    for (int i = 0; i < size; i++)
    {
        max = max > arr[i] ? max : arr[i];
    }

    return max;
}

template<>
const char *maxn(const char *arr[], int size)
{
    const char *tmp = nullptr;

    cout << arr[1] << endl;
    for (int i = 0; i < size; i++)
    {
        if (strlen(tmp) < strlen(arr[i]))
        {
            tmp = arr[i];
        }
    }

    return tmp;
}

int main()
{
    int *arr1 = new int[5];
    std::srand(time(nullptr));

    for (int i = 0; i < 5; i++)
    {
        arr1[i] = std::rand() % 100;
        cout << arr1[i] << "\t";
    }
    cout << endl;
    cout << "max: " << maxn<int>(arr1, 5) << endl;

    const char *arr3[3] = {"hello", "kdsjfdslkf", "xx"};
    cout << "longest: " << maxn<>(arr3, 3) << endl;

    return 0;
}
