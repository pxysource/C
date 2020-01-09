#include "tv.h"

void TV::setChannel(bool flag)
{
    if (flag)
    {
        if (_maxChannel == _channel)
        {
            _channel = 0;
        }
        else
        {
            _channel++;
        }
    }
    else
    {
        if (0 == _channel)
        {
            _channel = _maxChannel;
        }
        else
        {
            _channel--;
        }
    }
}

void TV::setVolume(bool flag)
{
    if (flag)
    {
        if (_volume < _maxChannel)
        {
            _volume++;
        }
    }
    else
    {
        if (_volume > 0)
        {
            _volume--;
        }
    }
}
