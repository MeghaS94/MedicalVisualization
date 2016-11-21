#ifndef VTKSLICE_H
#define VTKSLICE_H

#include <vtkImageReslice.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>
#include <vtkImageActor.h>

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
};

class vtkSliceInteractionCallback : public vtkCommand
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
    void Execute(vtkObject *, unsigned long event, void *); VTK_OVERRIDE

private:
    // Actions (slicing only, for now)
    int slicing;
    // Pointer to vtkImageReslice
    VTKSlice* slice;
    // Pointer to the interactor
    vtkRenderWindowInteractor* interactor;
};

#endif // VTKSLICE_H
