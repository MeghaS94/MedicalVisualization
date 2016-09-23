#ifndef VTKSURFACE_H
#define VTKSURFACE_H

#include "surface.h"
#include "vtkimagedata.h"
#include <string>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkMarchingContourFilter.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataConnectivityFilter.h>


using namespace std;

class VTKSurface : public Surface
{
private :
    //vtkSmartPointer<vtkImageData> volume;
    //vtkSmartPointer<vtkMarchingCubes> surface;
    vtkSmartPointer<vtkMarchingContourFilter> surface;
    vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter;
    VTKImageData* imageData;
    vtkSmartPointer<vtkImageData> modifiedData;
    float red; float blue; float green;
    int extent[6];
    double bounds[6];

public:
    VTKSurface(double isovalue_start, double isovalue_end);
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);
    void setImageData(ImageData* data);
    void render(Window *window);
    void createSurface();
    //double getIsovalue();

};

#endif // VTKSURFACE_H


