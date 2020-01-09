#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <cstring>
#include "bmpplay.h"
using namespace std;

class Bmp
{
private:
    char *_name;
    //图片参数结构体
    BITMAPFILEHEADER _fileheader;
    BITMAPINFOHEADER _infoheader;
    FileInfo _fd;
    char *_data;
    show_struct _show_struction;

public:
    Bmp (){}
    Bmp (const char *na);
    Bmp (const Bmp &r);
    ~Bmp ();
    void name ()const{cout << "bmp name: " << _name << endl;}
    void info (){
                            cout << "bmp width: " << _infoheader.biWidth << endl;
                            cout << "bmp height: " << _infoheader.biHeight << endl;
                            cout << "bmp size: " << _fileheader.bfSize << endl;
                }
    void getInfo ();
    int width (){return _infoheader.biWidth;}
    int height (){return _infoheader.biHeight;}
    int size (){return _fileheader.bfSize;}
    void setShowMsg (int refresh_flag=1, int offset_x=0, int offset_y=0);
    void showInLcd ();
};

#endif // BMP_H
