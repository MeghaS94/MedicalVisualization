#ifndef VOLUME_H
#define VOLUME_H

#include "window.h"
#include "slice.h"
#include "imagedata.h"
#include "layer.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Volume
{
protected:
    int voxel_count; //count of total number of voxels in the volume
    map<int, float> Map; //mapping the number of voxels to range of intensity
    float minIntensity ;
    float maxIntensity;
public:
    Volume();
    virtual void render(Window* window) = 0;
    virtual void setImageData(ImageData* data) = 0;
    virtual void setLayers(Layer* layers, int numberOfLayers) = 0;
    virtual void setCustomLayers(Layer* customLayers, int numberOfCustomLayers) = 0;
    virtual void createVolume() = 0;
    virtual void updateVOI(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax)=0;
    virtual void addPadding()=0;
    virtual void makeIntervals() =0;
    virtual void updatePlane(Slice* slice, int type)=0;
    virtual void axialPlane(bool visibility)=0;
    virtual void coronalPlane(bool visibility)=0;
    virtual void sagittalPlane(bool visibility)=0;
    virtual void updateTransferFunctions()=0;
    virtual void changeLayerMode(int mode)=0;
    float getMinIntensity();
    float getMaxIntensity();
};

#endif // VOLUME_H

