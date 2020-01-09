#include "bmp.h"

unsigned int Bmp::_copytimes = 0;

void Bmp::readInfo()
{
    //fstream构造函数关联文件名，就不用打开了，即构造函数关联文件，默认打开文件；
    //如果构造函数没有关联文件，则需要open打开；
    //总结：一个文件在一个程序中，不能在不关闭的情况下，打开多次，否则会读取错误
    //或则每次打开后，总是将文件关闭
    _bmpio.open(_bmpname, std::ios_base::in);
    if (!_bmpio.is_open())
    {
        cout << "Could not open bmp file" << _bmpname << endl;
        _bmpio.clear();
        return;
    }

    unsigned char bmp_info[_BMP_INFO_SIZE] = {0};
    this->_bmpio.read(reinterpret_cast<char *>(bmp_info), _BMP_INFO_SIZE);
    _bmpfileheader.bfType = bmp_info[0] << 8 | bmp_info[1] << 0;
    _bmpfileheader.bfSize = bmp_info[2] << 0 | bmp_info[3] << 8 |
                            bmp_info[4] << 16 | bmp_info[5] << 24;
    _bmpfileheader.bfOffBits = bmp_info[10] << 0 | bmp_info[11] << 8 |
                               bmp_info[12] << 16 | bmp_info[13] << 24;

    _bmpinfoheader.biSize = bmp_info[14] << 0 | bmp_info[15] << 8 |
                            bmp_info[16] << 16 | bmp_info[17] << 24;
    _bmpinfoheader.biWidth = bmp_info[18] << 0 | bmp_info[19] << 8 |
                             bmp_info[20] << 16 | bmp_info[21] << 24;
    _bmpinfoheader.biHeight = bmp_info[22] << 0 | bmp_info[23] << 8 |
                              bmp_info[24] << 16 | bmp_info[25] << 24;
    _bmpinfoheader.biPlanes = bmp_info[26] << 0 | bmp_info[27] << 8;
    _bmpinfoheader.biBitCount = bmp_info[28] << 0 | bmp_info[29] << 8;
    _bmpinfoheader.biCompression = bmp_info[30] << 0 | bmp_info[31] << 8 |
                                   bmp_info[32] << 16 | bmp_info[33] << 24;
    _bmpinfoheader.biSizeImage = bmp_info[34] << 0 | bmp_info[35] << 8 |
                                 bmp_info[36] << 16 | bmp_info[37] << 24;
    _bmpinfoheader.biXPelsPerMeter = bmp_info[38] << 0 | bmp_info[39] << 8 |
                                     bmp_info[40] << 16 | bmp_info[41] << 24;
    _bmpinfoheader.biYPelsPerMeter = bmp_info[42] << 0 | bmp_info[43] << 8 |
                                     bmp_info[44] << 16 | bmp_info[45] << 24;
    _bmpinfoheader.biClrUsed = bmp_info[46] << 0 | bmp_info[47] << 8 |
                               bmp_info[48] << 16 | bmp_info[49] << 24;
    _bmpinfoheader.biClrImportant = bmp_info[50] << 0 | bmp_info[51] << 8 |
                                    bmp_info[52] << 16 | bmp_info[53] << 24;
    _bmpio.close();
}

Bmp::Bmp()
    :_bmpio()
{

}

Bmp::Bmp(const char *filename)
    :_bmpio(), _bmpname(filename)
{
    readInfo();
}

Bmp::Bmp(Bmp & r)
{
    string::size_type pos;
    string::size_type n;
    char buf[1024];
    bzero (buf, sizeof(buf));

    _copytimes++;
    this->_bmpname = r._bmpname;

    pos = this->_bmpname.find("-copy");
    //不是从拷贝的文件拷贝
    if (std::string::npos == pos)
    {
        pos = this->_bmpname.find(".bmp");
        this->_bmpname.insert(pos, "-copy");
        pos = this->_bmpname.find(".bmp");
        this->_bmpname.insert(pos, std::to_string(_copytimes));
    }
    else
    {
        //"-copy"后面的数字根据复制的次数变更
        pos++;
        //需要替换的字符数量
        n = this->_bmpname.find(".bmp") - _bmpname.find_last_of("-copy") - 1;
        this->_bmpname.replace(pos, n, std::to_string(_copytimes));
    }

    r._bmpio.open(r._bmpname);
    if (!r._bmpio.is_open())
    {
        cout << "Error: open read file failed!" << endl;
    }

    this->_bmpio.open(this->_bmpname, std::ios_base::out |
                      std::ios_base::trunc);
    if (!_bmpio.is_open())
    {
        cout << "Error: open write file failed!" << endl;
    }

    while (r._bmpio.read(buf, sizeof(buf)))
    {
        this->_bmpio.write(buf, r._bmpio.gcount());
        bzero(buf, sizeof(buf));
    }
    this->_bmpio.write(buf, r._bmpio.gcount());

    r._bmpio.close();
    this->_bmpio.close();
    this->readInfo();
}

const string & Bmp::bmpName() const
{
    cout << "Bmp file name: " << _bmpname << endl;
    return _bmpname;
}

Bmp & Bmp::operator =(const Bmp & r)
{
    if (this->_bmpname == r._bmpname)
    {
        return *this;
    }

    this->_bmpname = r._bmpname;
    this->readInfo();
    return *this;
}

void Bmp::bmpInfo()
{
    cout << "Bmp info: " << endl;
    cout << "==================Bmp File Header===================" << endl;
    cout << "Bmp file type: " << (char)(_bmpfileheader.bfType>>8)
         << (char)(_bmpfileheader.bfType&0x00ff) << endl;
    cout << "Bmp file size:" << _bmpfileheader.bfSize << endl;
    cout << "Bmp header size:" << _bmpfileheader.bfOffBits << endl;
    cout << "==================Bmp Info Header===================" << endl;
    cout << "Bmp info header size: " << _bmpinfoheader.biSize << endl;
    cout << "Bmp width : " << _bmpinfoheader.biWidth << endl;
    cout << "Bmp height: " << _bmpinfoheader.biHeight << endl;
    cout << "Bmp target device level: " << _bmpinfoheader.biPlanes << endl;
    cout << "Bmp bits of a pixel: " << _bmpinfoheader.biBitCount << endl;
    cout << "Bmp compression type: " << _bmpinfoheader.biCompression << endl;
    cout << "Bmp size: " << _bmpinfoheader.biSizeImage << endl;
    cout << "Bmp X resolution: " << _bmpinfoheader.biXPelsPerMeter << endl;
    cout << "Bmp Y resolution: " << _bmpinfoheader.biYPelsPerMeter << endl;
    cout << "Bmp used color: " << _bmpinfoheader.biClrUsed << endl;
    cout << "Bmp important color: " << _bmpinfoheader.biClrImportant << endl;
    cout << "====================================================" << endl;
}
