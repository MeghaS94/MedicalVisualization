#ifndef SURFACE_H
#define SURFACE_H

#include <string>
#include "window.h"

using namespace std;

class Surface
{
public:
    Surface(double isovalue_s, double isovalue_end);
    void virtual render(Window *window) = 0;
    void virtual readData(string foldername) = 0;
    void virtual createSurface() = 0;
    double getIsovalueStart();
    double getIsovalueEnd();

protected:
    double isovalue_start; //bone, tissue etc
    double isovalue_end; //bone, tissue etc
};

#endif // SURFACE_H
