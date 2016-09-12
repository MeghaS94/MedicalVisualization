#ifndef VOLUME_H
#define VOLUME_H

#include "window.h"
#include "slice.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Volume
{
protected:
    int voxel_count; //count of total number of voxels in the volume
public:
    map<int, float> Map; //mapping the number of voxels to range of intensity
    float minIntensity ;
    float maxIntensity;
    Volume();
    void virtual render(Window* window) = 0;
    void virtual readData(string foldername) = 0;
    void virtual createVolume() = 0;
    void virtual makeIntervals() =0;
    void virtual updatePlane(Slice* slice, int type)=0;
};

#endif // VOLUME_H

