#ifndef VTKSURFACE_H
#define VTKSURFACE_H

#include "surface.h"
#include "vtkimagedata.h"
#include <string>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkUnsignedCharArray.h>
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
#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindow.h>
#include "QVTKInteractorAdapter.h"
#include "QVTKInteractor.h"
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <qevent.h>
#include <vtkVertexGlyphFilter.h>

using namespace std;

struct compareFunc
{
    inline bool operator() (const vtkSmartPointer<vtkCellArray>& arr1, const vtkSmartPointer<vtkCellArray>& arr2)
    {
        return (arr1->GetNumberOfCells() > arr2->GetNumberOfCells());
    }
};

struct Annotation{
    float x;
    float y;
    float z;
    string text;
    float r;
    float g;
    float b;
    //Actor
    //Renderer
    //point id's
};

class MouseInteractorStylePP;

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
    vtkSmartPointer<vtkCellArray> celldata2;
    vtkSmartPointer<vtkPolyData> data2;
    long long small;
    long long big;
    vtkSmartPointer<vtkActor> actor;
    vector<vtkSmartPointer<vtkActor> > actor1;
    vtkSmartPointer<vtkActor> actor2;
    vtkSmartPointer<vtkPolyDataMapper> mapper1;
    vtkSmartPointer<vtkPolyDataMapper> mapper2;
    bool pick;
    vtkSmartPointer<MouseInteractorStylePP> style ;
    //spacing
    double spacing_x;
    double spacing_y;
    double spacing_z;

public:
    VTKSurface(double isovalue_start, double isovalue_end);
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);

    void mousePressEvent(QMouseEvent *event);

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
    void changeMode(int mode);
    void addAnnotation();
    void print();
    void setSpacing(vector<double> spacing);

};

#endif // VTKSURFACE_H


