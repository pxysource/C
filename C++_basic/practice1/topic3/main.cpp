/*************************************************************
 *3.编写一个程序，计算N升纯净水所包含的分子个数，结果用科学计数法表示。
 * ***********************************************************/

#include <iostream>
using namespace std;

int main ()
{
    int n;
    cout << "Please input n litre of water: " << endl;
    cin >> n;

    int mol = 18;
    double mol_num = 6.24e+23;
    double number = mol_num * n * 1000 / mol;

    cout << n << " litre water have ";
    cout.setf (ios_base::scientific);
    cout << number << " hydrone" << endl;

    return 0;
}
