#ifndef VTKSURFACE_H
#define VTKSURFACE_H

#include "surface.h"
#include <string>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkMarchingContourFilter.h>
#include <vtkDICOMImageReader.h>

using namespace std;

class VTKSurface : public Surface
{
private :
    vtkSmartPointer<vtkImageData> volume;
    //vtkSmartPointer<vtkMarchingCubes> surface;
    vtkSmartPointer<vtkMarchingContourFilter> surface;
    vtkSmartPointer<vtkDICOMImageReader> reader;
    float red; float blue; float green;

public:
    VTKSurface(double isovalue_start, double isovalue_end);
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);
    void readData(string foldername);
    void render(Window *window);
    void createSurface();
    //double getIsovalue();

};

#endif // VTKSURFACE_H


