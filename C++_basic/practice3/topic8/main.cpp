#include <iostream>
using namespace std;

class TV;

class Remote
{
private:

public:

    void selectChannel (TV &r, unsigned int channel);
    void selectVolume (TV &r, unsigned int volume);
    void addorIncChannel (TV &r, bool flag);
    void addorIncVolume (TV &r, bool flag);
};

class TV
{
private:
    unsigned int _channel;
    unsigned int _volume;
    const unsigned int _maxChannel;
    const unsigned int _maxVolume;
public:
    TV (unsigned int maxChannel=100, unsigned int maxVolume=100):_maxChannel(maxChannel),\
        _maxVolume(maxVolume){_channel = 0; _volume = 0;}
    void setChannel (bool flag);
    void setVolume (bool flag);
    void showChannel (){cout << "channel: " << _channel << endl;}
    void showVolume (){cout << "volume: " << _volume << endl;}
    friend void Remote::selectChannel (TV &r, unsigned int channel);
    friend void Remote::selectVolume (TV &r, unsigned int volume);
    friend void Remote::addorIncChannel (TV &r, bool flag);
    friend void Remote::addorIncVolume (TV &r, bool flag);
};

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

void Remote::selectChannel(TV &r, unsigned int channel)
{
    if (channel > r._maxChannel)
    {
        cout << "Error: remote selectChannel error!" << endl;
    }
    else
    {
        r._channel = channel;
    }
}

void Remote::selectVolume(TV &r, unsigned int volume)
{
    if (volume > r._maxVolume)
    {
        cout << "Error: remote selectVolume error!" << endl;
    }
    else
    {
        r._volume = volume;
    }
}

void Remote::addorIncChannel(TV &r, bool flag)
{
    r.setChannel(flag);
}

void Remote::addorIncVolume(TV &r, bool flag)
{
    r.setVolume(flag);
}

int main()
{
    TV tcl;
    tcl.showChannel();
    tcl.showVolume();
    tcl.setChannel(0);
    tcl.setVolume(0);
    tcl.showChannel();
    tcl.showVolume();

    Remote r1;
    r1.addorIncChannel(tcl, 1);
    r1.addorIncVolume(tcl, 1);
    tcl.showChannel();
    tcl.showVolume();

    r1.selectChannel(tcl, 45);
    r1.selectVolume(tcl, 45);
    tcl.showChannel();
    tcl.showVolume();

    return 0;
}
