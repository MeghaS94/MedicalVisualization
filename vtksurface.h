#ifndef VTKSURFACE_H
#define VTKSURFACE_H

#include "surface.h"
#include "vtkimagedata.h"
#include <string>
#include <vtkSmartPointer.h>
#include <vtkContourFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkMarchingContourFilter.h>
#include <vtkDICOMImageReader.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkCellArray.h>
#include <map>
#include <set>

using namespace std;

class VTKSurface : public Surface
{
private :
    //vtkSmartPointer<vtkImageData> volume;
    //vtkSmartPointer<vtkMarchingCubes> surface;
    vtkSmartPointer<vtkContourFilter> surface;
    vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter;
    VTKImageData* imageData;
    vtkSmartPointer<vtkImageData> modifiedData;
    vtkSmartPointer<vtkCellArray> polyArray; //Array of triangles
    vector<vtkSmartPointer<vtkCellArray> > connectedComponents;
    float red; float blue; float green;
    int extent[6];
    double bounds[6];
    map <vtkIdType, bool> Array;
    vtkSmartPointer<vtkCellLinks> cellLinksFilter;
    Layer* layers;
    int count;
    int numberOfLayers;

public:
    VTKSurface(double isovalue_start, double isovalue_end);
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);
    void setImageData(ImageData* data);
    void setLayers(Layer* layers, int n);
    void render(Window *window);
    void createSurface();
    void makeConnectedSurfaces();
    void makeConnectedSurfaces2();
    void findConnectedVertsRecur(vtkIdType ID);
    //double getIsovalue();

};

#endif // VTKSURFACE_H


