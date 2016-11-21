#ifndef SLICE_H
#define SLICE_H

#include <string>
#include "window.h"
#include "imagedata.h"

using namespace std;

class Volume;

class Slice
{
public:
    Slice(int type);
    virtual void render(Window *window) = 0;
    virtual void setImageDataVolume(ImageData* data, Volume* volume) = 0;
    virtual void createSlice() = 0;
    virtual void updateSlice() = 0;
    int getType();
    virtual double getPosition() = 0;
    virtual void updateTransferFunction() = 0;

protected:
    int type; //1 for axial, 2 for coronal, 3 for sagittal
};

#endif // SLICE_H
