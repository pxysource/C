#ifndef REMOTE_H
#define REMOTE_H

#include <iostream>
using std::cout;
using std::endl;

class TV;

class Remote
{
private:

public:
    Remote ();
    void selectChannel (TV &r, unsigned int channel);
    void selectVolume (TV &r, unsigned int volume);
    void addorIncChannel (TV &r, bool flag);
    void addorIncVolume (TV &r, bool flag);
};

#endif // REMOTE_H
