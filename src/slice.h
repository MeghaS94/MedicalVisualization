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
    virtual int getType()=0;
    virtual double getPosition() = 0;
    virtual void updateTransferFunction() = 0;
    virtual vector<double> intensity() = 0;
    virtual void createHistogram() = 0;
    virtual vector< vector<double> >  getPointsOnSlice() =0;
    virtual vector< double> getIntensityRange() =0;
    virtual void setSliceMode(bool status) = 0;
    virtual bool getSliceMode() = 0;
protected:
    int type; //1 for axial, 2 for coronal, 3 for sagittal
    vector< vector<double> >  points_on_slice;
};

#endif // SLICE_H
