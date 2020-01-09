#ifndef TV_H
#define TV_H

#include <iostream>
using std::cout;
using std::endl;

class Remote;

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
    //friend void Remote::selectChannel (TV &r, unsigned int channel);
    //friend void Remote::selectVolume (TV &r, unsigned int volume);
    //friend void Remote::addorIncChannel (TV &r, bool flag);
    //friend void Remote::addorIncVolume (TV &r, bool flag);
    friend class Remote;
};

#endif // TV_H
