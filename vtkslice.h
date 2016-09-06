#ifndef VTKSLICE_H
#define VTKSLICE_H

#include <vtkImageReslice.h>
#include <vtkImageReader2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCommand.h>

#include "slice.h"
#include "controller.h"

class VTKSlice : public Slice
{
private :
    vtkSmartPointer<vtkImageReslice> slice;
    vtkSmartPointer<vtkImageReader2> data;
    Controller* controller;

public:
    VTKSlice(int type, Controller* c);
    vtkSmartPointer<vtkImageReslice> getSlice();
    vtkSmartPointer<vtkImageReader2> getData();
    Controller* getController();
    void readData(string foldername);
    void createSlice();
    void render(Window *window );
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
