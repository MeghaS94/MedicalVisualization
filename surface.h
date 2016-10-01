#ifndef SURFACE_H
#define SURFACE_H

#include <string>
#include "window.h"
#include "imagedata.h"
#include "layer.h"

using namespace std;

class Surface
{
public:
    Surface(double isovalue_s, double isovalue_end);
    virtual void render(Window *window) = 0;
    virtual void setImageData(ImageData* data) = 0;
    virtual void setLayers(Layer* layers, int n) = 0;
    virtual void createSurface() = 0;
    double getIsovalueStart();
    double getIsovalueEnd();
    void setIsovalueStart(double val);
    void setIsovalueEnd(double val);

protected:
    double isovalue_start; //bone, tissue etc
    double isovalue_end; //bone, tissue etc
};

#endif // SURFACE_H
