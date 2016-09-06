
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include "vtksurface.h"
#include "window.h"
#include "vtkwindow.h"


VTKSurface::VTKSurface(double isoValue) : Surface(isoValue)
{
    volume = vtkSmartPointer<vtkImageData>::New();
    reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    surface = vtkSmartPointer<vtkMarchingCubes>::New();
}

void VTKSurface::readData(string foldername)
{
    reader->SetDirectoryName(foldername.c_str());
    reader->Update();
    volume->DeepCopy(reader->GetOutput());
}

void VTKSurface::createSurface()
{
    surface->SetInputData(volume);
    surface->ComputeNormalsOn();
    surface->SetValue(0, isovalue);
    //surface->update();
}

void VTKSurface::render(Window *window)
{
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //renderer->SetBackground(.1, .2, .3);
    renderer->AddActor(actor);

    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(.0, .0, .0);
    renderer->ResetCamera();
}


