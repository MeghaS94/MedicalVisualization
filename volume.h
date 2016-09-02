#ifndef VOLUME_H
#define VOLUME_H

#include "window.h"
#include <string>

using namespace std;

class Volume
{
public:
    Volume();
    void virtual render(Window *window) = 0;
    void virtual readData(string foldername) = 0;
    void virtual createVolume() = 0;
};

#endif // VOLUME_H
