#include "remote.h"
#include "tv.h"

Remote::Remote()
{

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
