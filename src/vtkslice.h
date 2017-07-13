#ifndef VTKSLICE_H
#define VTKSLICE_H

#include <vtkImageReslice.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkImageActor.h>
#include "QVTKInteractorAdapter.h"
#include "QVTKInteractor.h"

#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>

#include "slice.h"
#include "controller.h"
#include "vtkimagedata.h"
#include "vtkvolume.h"



class VTKSlice : public Slice
{
private :
    vtkSmartPointer<vtkImageReslice> slice;
    vtkSmartPointer<vtkRenderer>  renderer;
    VTKImageData* imageData;
    Controller* controller;
    VTKVolume* volume;
    vtkSmartPointer<vtkImageActor> actor;
    //a vector to store the points marked on a slice
    vector< vector<double> > pts;
    vector< double> intensityRange;

    bool pickPtsOnSliceMode;

public:
    VTKSlice(int type, Controller* c);
    vtkSmartPointer<vtkImageReslice> getSlice();
    vtkSmartPointer<vtkImageData> getData();
    Controller* getController();
    void setImageDataVolume(ImageData* data, Volume* volume);
    void createSlice();
    void updateSlice();
    void render(Window *window );
    double getPosition();
    int getType();
    void updateTransferFunction();
    vector<double> intensity();
    void createHistogram();
    vector< vector<double> > getPointsOnSlice();
    void setPointsOnSlice(vector< vector<double> > points);
    vector< double> getIntensityRange();
    void setIntensityRange(vector< double> I);


    void setSliceMode(bool status);
    bool getSliceMode();
};

class vtkSliceInteractionCallback :  public vtkCommand
{
public:
    static vtkSliceInteractionCallback *New()
    {
        return new vtkSliceInteractionCallback;
    }
    vtkSliceInteractionCallback();
    void SetSlice(VTKSlice* slice);
    VTKSlice* GetSlice();
    void SetInteractor(vtkRenderWindowInteractor* interactor);
    vtkRenderWindowInteractor* GetInteractor();
    vector<double> getSelectedIntensityRange();
    //get count of number of polygon points , after a certain number, call the above range func
    int getCountofPoints();
    void Execute(vtkObject *, unsigned long event, void *); VTK_OVERRIDE
    bool pointInPolygon(double x, double y, double z);
    vector< vector<double> > getPolygonPoints();

private:
    vtkSmartPointer<vtkPolygon> polygon;
    vector<float> points; //or int count_of_points
    int CountofPoints;
    // Actions (slicing only, for now)
    int slicing;
    // Pointer to vtkImageReslice
    VTKSlice* slice;
    // Pointer to the interactor
    vtkRenderWindowInteractor* interactor;
    vector< vector<double> > polygon_points; //points that form the polygon (selected region)
};



#endif // VTKSLICE_H
