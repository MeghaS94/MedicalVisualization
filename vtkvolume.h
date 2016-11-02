#ifndef VTKVOLUME_H
#define VTKVOLUME_H

#include <QWidget>
#include "window.h"
#include "volume.h"
#include "vtkimagedata.h"
#include <vtkVolume.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <string>
#include <vtkPlaneSource.h>
#include <vtkActor.h>
#include <vtkImageData.h>
#include <vtkExtractVOI.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>

#include "slice.h"
#include "layer.h"

using namespace std;

class VTKVolume : public Volume
{
private :
    vtkSmartPointer<vtkVolume> volume;
    vtkSmartPointer<vtkExtractVOI> extractVOI;
    VTKImageData* imageData;
    vtkSmartPointer<vtkRenderer> volumeRenderer;
    vtkSmartPointer<vtkPlaneSource> plane1;
    vtkSmartPointer<vtkPlaneSource> plane2;
    vtkSmartPointer<vtkPlaneSource> plane3;
    vtkSmartPointer<vtkActor> actor1;
    vtkSmartPointer<vtkActor> actor2;
    vtkSmartPointer<vtkActor> actor3;
    vtkSmartPointer<vtkColorTransferFunction> colorFun;
    vtkSmartPointer<vtkPiecewiseFunction> opacityFun;
    int extent[6];
    double bounds[6];
    float colours[15][2][3] = {{{0.2,0,0},{1,0,0}},
                                {{0,0.2,0},{0,1,0}},
                                {{0,0,0.2},{0,0,1}},
                                {{0.2,0.2,0},{1,1,0}},
                                {{0.2,0,0.2},{1,0,1}},
                                {{0,0.2,0.2},{0,1,1}},
                                {{1,1,1},{0.5,0.5,0.5}},
                                {{0.2,0.8,0},{1,0.8,0}},
                                {{0,0.8,0.2},{0,0.8,1}},
                                {{0.8,0.2,0},{0.8,1,0}},
                                {{0.8,0,0.2},{0.8,0,1}},
                                {{0.2,0,0.8},{1,0,0.8}},
                                {{0,0.2,0.8},{0,1,0.8}},
                                {{0.2,0.8,0.8},{1,0.8,0.8}},
                                {{0.8,0.2,0.8},{0.8,1,0.8}}};
    Layer* layers;
    int numberOfLayers;

public:
    VTKVolume();
    void setImageData(ImageData* data);
    void setLayers(Layer* layers, int n);
    void createVolume();
    void updateVOI(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);
    void addPadding();
    void render(Window *window);
    void updateTransferFunctions();
    void updatePlane(Slice* slice, int type);    
    void makeIntervals();
    void axialPlane(bool visibility);
    void coronalPlane(bool visibility);
    void sagittalPlane(bool visibility);
    void changePlanes();
};  

#endif // VTKVOLUME_H

