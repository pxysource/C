#include "bmp.h"

Bmp::Bmp(const char *na)
{
    int len = strlen (na);
    _name = new char[len + 1];
    memcpy (_name, na, len + 1);
    _data = NULL;
    memset (&_fileheader, 0, sizeof(_fileheader));
    memset (&_infoheader, 0, sizeof(_infoheader));
    memset (&_fd, 0, sizeof(_fd));
    _show_struction.offset_x = 0;
    _show_struction.offset_y = 0;
    _show_struction.refresh_flag = 1;
}

Bmp::Bmp(const Bmp &r)
{
    if (this == &r)
    {
        return;
    }

    int len = strlen (r._name);
    this->_name = new char[len + 1];
    memcpy (this->_name, r._name, len + 1);

    unsigned long content_len = strlen (r._data);
    this->_data = (char *)malloc(content_len + 1);
    memcpy (this->_data, r._data, content_len + 1);

    this->_fd = r._fd;
    this->_fileheader = r._fileheader;
    this->_infoheader = r._infoheader;
    this->_show_struction = r._show_struction;
}

Bmp::~Bmp()
{
    if (NULL != _data)
    {
        free (_data);
        _data = NULL;
    }

    delete [] _name;
}

void Bmp::getInfo()
{
    if (NULL != _data)
    {
        free (_data);
        _data = NULL;
    }

    BmpInit (&_fd, _name);
    _data = ReadBmpData(_fd, &_fileheader, &_infoheader);
    close (_fd.bmp_fd);
}

void Bmp::setShowMsg(int refresh_flag, int offset_x, int offset_y)
{
    if (0 == refresh_flag)
    {
        _show_struction.refresh_flag = 0;
    }
    else
    {
        _show_struction.refresh_flag = 1;
    }

    if (offset_x < 0 || offset_x > Width)
    {
        cout << "Error: setShowMsg() set offset_x failed!" << endl;
        _show_struction.offset_x = 0;
    }
    else
    {
        _show_struction.offset_x = offset_x;
    }

    if (offset_y < 0 || offset_y > Width)
    {
        cout << "Error: setShowMsg() set offset_y failed!" << endl;
        _show_struction.offset_y = 0;
    }
    else
    {
        _show_struction.offset_y = offset_y;
    }
}

void Bmp::showInLcd()
{
    BmpPlay(_name, &_fd, _show_struction, &_fileheader, &_infoheader);
}
