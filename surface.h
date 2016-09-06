#ifndef SURFACE_H
#define SURFACE_H

#include <string>
#include "window.h"

using namespace std;

class Surface
{
public:
    Surface(double isovalue);
    void virtual render(Window *window) = 0;
    void virtual readData(string foldername) = 0;
    void virtual createSurface() = 0;
    double getIsovalue();

protected:
    double isovalue; //bone, tissue etc
};

#endif // SURFACE_H
