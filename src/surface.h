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
    virtual void createSurface1() = 0;
    virtual double getIsovalueStart()=0;
    virtual double getIsovalueEnd()=0;
    virtual void setIsovalueStart(double val)=0;
    virtual void setIsovalueEnd(double val)=0;
    virtual void showCompleteSurface() = 0;
    virtual void showComponentSurface() = 0;
    virtual void showNextSurface() = 0;
    virtual void showPreviousSurface() = 0;
    virtual int getCurrentSurface() = 0;
    virtual long getNumberOfTriangles(bool status) = 0;
    virtual long getMinimum() = 0;
    virtual long getMaximum() = 0;
    virtual void updateThreshold(int val) = 0;
    virtual void removeSurfaces() = 0;
    virtual void removeSurface() = 0;
    virtual void changeMode(int mode) = 0;
    virtual void addAnnotation() = 0;
    virtual void print() = 0;
    virtual void setSpacing(vector<double> spacing)=0;

    virtual vector < vector<double> > getPtsOnSlice()=0;
    virtual void setPtsOnSlice(vector < vector<double> > pts)=0;

protected:
    double isovalue_start; //bone, tissue etc
    double isovalue_end; //bone, tissue etc
    vector < vector<double> > points_on_slice;
};

#endif // SURFACE_H
