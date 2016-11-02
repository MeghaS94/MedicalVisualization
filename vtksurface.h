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
#include <vtkPolyDataNormals.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <map>
#include <set>

using namespace std;

struct compareFunc
{
    inline bool operator() (const vtkSmartPointer<vtkCellArray>& arr1, const vtkSmartPointer<vtkCellArray>& arr2)
    {
        return (arr1->GetNumberOfCells() > arr2->GetNumberOfCells());
    }
};

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
    vector<int> numberOfOpenEdges;
    float red; float blue; float green;
    int extent[6];
    double bounds[6];
    map <vtkIdType, bool> Array;
    map <vtkIdType, bool> Array2;
    vtkSmartPointer<vtkCellLinks> cellLinksFilter;
    vtkSmartPointer<vtkPolyData> surfacePolygons;
    vtkSmartPointer<vtkPolyData> wholeSurfacePolygons;
    vtkSmartPointer<vtkRenderer> renderer;
    vector<vtkIdType*> subsurfaces;
    Layer* layers;
    int count;
    int numberOfLayers;
    int current_surface;
    bool whole;
    int threshold;
    vtkSmartPointer<vtkCellArray> celldata[2];
    vtkSmartPointer<vtkPolyData> data[2];
    long long small;
    long long big;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkActor> actor1;
    vtkSmartPointer<vtkActor> actor2;
    vtkSmartPointer<vtkPolyDataMapper> mapper1;
    vtkSmartPointer<vtkPolyDataMapper> mapper2;

public:
    VTKSurface(double isovalue_start, double isovalue_end);
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);
    void setImageData(ImageData* data);
    void setLayers(Layer* layers, int n);
    void render(Window *window);
    void createSurface();
    void makeConnectedSurfaces();
    long findConnectedVertsRecur(vtkIdType ID);
    void createConnectedSurfaces();    
    void showCompleteSurface();
    void showComponentSurface();
    void showNextSurface();
    void showPreviousSurface();
    long getMinimum();
    long getMaximum();
    void updateThreshold(int val);
    void removeSurfaces();
    void removeSurface();
    int getCurrentSurface();
    long getNumberOfTriangles(bool status);

};

#endif // VTKSURFACE_H


