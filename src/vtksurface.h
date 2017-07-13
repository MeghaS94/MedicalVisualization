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

struct compareFunc // to sort two cell arrays based on size
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
    vtkSmartPointer<vtkActor> actor; // actor of annotation
    vtkSmartPointer<vtkActor> surfaceActor; // actor of the surface to which the annotation belongs
    vtkSmartPointer<vtkActor2D> textActor; // actor for the annotation text
    int index;
};

class MouseInteractorStylePP;

class VTKSurface : public Surface
{
private :
    vtkSmartPointer<vtkContourFilter> surface;
    VTKImageData* imageData;
    vtkSmartPointer<vtkImageData> modifiedData; // modifed to 1-0 volume, i.e 1 for values within isovalue range, 0 otherwise
    vtkSmartPointer<vtkCellArray> polyArray; //Array of triangles
    vector<vtkSmartPointer<vtkCellArray> > connectedComponents; //vector of cell arrays (arrays of triangles)
    vector<int> numberOfOpenEdges;
    float red; float blue; float green;
    int extent[6];
    double bounds[6];
    map <vtkIdType, bool> Array; // map to keep track of covered points
    map <vtkIdType, bool> Array2; // map to keep track of covered cells or triangles
    vtkSmartPointer<vtkCellLinks> cellLinksFilter;
    vtkSmartPointer<vtkPolyData> surfacePolygons;
    vtkSmartPointer<vtkPolyData> wholeSurfacePolygons;
    vtkSmartPointer<vtkRenderer> renderer;
    vector<vtkIdType*> subsurfaces; // vector of triangles of the current connected component
    Layer* layers;
    int count;
    int numberOfLayers;
    int current_surface;
    bool whole;
    int threshold;
    vtkSmartPointer<vtkCellArray> celldata2; // to show the part of the surface with number of triangles below threshold
    vtkSmartPointer<vtkPolyData> data2; // to show the part of the surface with number of triangles below threshold
    long long small;
    long long big;
    vtkSmartPointer<vtkActor> actor; // actor for whole surface
    vector<vtkSmartPointer<vtkActor> > actor1; // vector of actors for each visible component surface
    vector<vtkSmartPointer<vtkActor> > allActors; // vector of all actors
    vector<bool> visible; // vector to mark visibility of each component
    vtkSmartPointer<vtkActor> actor2; // for celldata2
    vtkSmartPointer<vtkPolyDataMapper> mapper2; // for celldata2
    bool pick;
    vtkSmartPointer<MouseInteractorStylePP> style ;
    //spacing
    double spacing_x;
    double spacing_y;
    double spacing_z;

public:
    VTKSurface(double isovalue_start, double isovalue_end, float r, float g, float b);
    vector<vtkSmartPointer<vtkActor> > getActors();
    void setImageData(ImageData* data);
    void setLayers(Layer* layers, int n);
    void render(Window *window);
    void createSurface();
    void createSurface1();
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

    vector<double> returnClosestPoint(double x, double y, double z);
    void recur(double x, double y, double z);
    double getIsovalueStart();
    double getIsovalueEnd();
    void setIsovalueStart(double val);
    void setIsovalueEnd(double val);
    vector < vector<double> > getPtsOnSlice();
    void setPtsOnSlice(vector < vector<double> > pts);
};

#endif // VTKSURFACE_H


