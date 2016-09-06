#ifndef VTKSURFACE_H
#define VTKSURFACE_H

#include "surface.h"
#include <string>
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>

using namespace std;

class VTKSurface : public Surface
{
private :
    vtkSmartPointer<vtkImageData> volume;
    vtkSmartPointer<vtkMarchingCubes> surface;
    vtkSmartPointer<vtkDICOMImageReader> reader;

public:
    VTKSurface(double isoValue);
    void readData(string foldername);
    void render(Window *window);
    void createSurface();
    //double getIsovalue();

};

#endif // VTKSURFACE_H

