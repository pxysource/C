#include "complexnumber.h"

ComplexNumber::ComplexNumber(double real_part, double image_part)
{
    _real = real_part;
    _image = image_part;
}

ComplexNumber ComplexNumber::operator+(ComplexNumber &r)
{
    ComplexNumber tmp;
    tmp._image = this->_image + r._image;
    tmp._real = this->_real + r._real;

    return tmp;
}

ComplexNumber ComplexNumber::operator-(ComplexNumber &r)
{
    ComplexNumber tmp;
    tmp._image = this->_image - r._image;
    tmp._real = this->_real - r._real;

    return tmp;
}

ComplexNumber ComplexNumber::operator*(ComplexNumber &r)
{
    ComplexNumber tmp;
    tmp._real = this->_real * r._real - this->_image * r._image;
    tmp._image = this->_image * r._real + this->_real * r._image;

    return tmp;

}

ComplexNumber ComplexNumber::operator/(ComplexNumber &r)
{
    ComplexNumber tmp;
    tmp._real = (this->_real * r._real + this->_image * r._image) /\
            (r._real * r._real + r._image * r._image);
    tmp._image =(this->_image * r._real - this->_real * r._image) /\
            (r._real * r._real + r._image * r._image);

    return tmp;
}

ostream & operator<<(ostream &os, ComplexNumber &co)
{
    if (co._image > 0)
    {
        os << co._real << " + " << co._image << "i";
    }
    else if (0 == co._image)
    {
        os << co._real;
    }
    else
    {
        co._image = -1 * (co._image);
        os << co._real << " - " << co._image << "i";
    }

    return os;
}
