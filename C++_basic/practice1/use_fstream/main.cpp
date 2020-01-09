/****************************************************
 *9.使用文件类 fstream，完成文件的复制。（文件IO、类与对象）
 * **************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main (void)
{
    fstream rFile;
    fstream cFile;
    char buf[1024];

    rFile.open("read.txt", ios_base::in);
    if (!rFile.is_open())
    {
        cout << "Open read.txt failed!" << endl;
    }

    cFile.open("copy.txt", ios_base::out);
    if (!cFile.is_open())
    {
        cout << "Open copy.txt failed!" << endl;
    }

    for (int i; memset (buf, 0, sizeof(buf)),
         rFile.read (buf, sizeof(buf)), i = rFile.gcount();)
    {
        cout << "i: " << i << endl;
        cout << "copying......" << endl;
        cFile.write (buf, i);
    }

    return 0;
}
