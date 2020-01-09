/**********************************************************
 *7.编写一个函数，计算一个圆锥体的体积，并且在不指定高度时，
 * 默认高度按照1计算，底部半径没有默认值。（函数默认参数）
 * ********************************************************/
#include <iostream>
using namespace std;

#define PI 3.14

double get_volume (double r, double h=1)
{
    double ret;
    ret = PI * r * r * h / 3;
    return ret;
}

int main ()
{
    double radius;
    double height;

    while (1)
    {
        cout << "Please input circular cone radius: ";
        cin >> radius;
        cout << "Please input circular cone height (0 to default): ";
        cin >> height;
        if (radius <= 0 || height < 0)
        {
            cout << "Input error, exit!" << endl;
            break;
        }

        if (0 == height)
        {
            cout << "volume of circular cone (" << "radius=" << radius << ",";
            cout << "height=" << 1 << "): " << get_volume (radius) << endl;
        }
        else
        {
            cout << "volume of circular cone (" << "radius=" << radius << ",";
            cout << "height=" << height << "): " << get_volume (radius, height) << endl;
        }

    }

    return 0;
}
