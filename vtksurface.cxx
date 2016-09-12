#include <vtkActor.h>
#include <vtkMarchingContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkContourFilter.h>
#include "vtksurface.h"
#include "window.h"
#include "vtkwindow.h"


VTKSurface::VTKSurface(double isoValue_start, double isoValue_end) : Surface(isoValue_start, isoValue_end)
{
    volume = vtkSmartPointer<vtkImageData>::New();
    reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkMarchingContourFilter>::New();
}

VTKSurface::VTKSurface(double isoValue_start, double isoValue_end, float r, float g, float b) : Surface(isoValue_start, isoValue_end)
{
    volume = vtkSmartPointer<vtkImageData>::New();
    reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkMarchingContourFilter>::New();
    red = r; blue = b; green =g;
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
    surface->SetValue(isovalue_start, isovalue_end);
    //surface->update();
}

void VTKSurface::render(Window *window)
{
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    //actor.SetNumberOfCloudPoints( 1000000 );
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(red, blue, green);
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //renderer->SetBackground(.1, .2, .3);
    renderer->AddActor(actor);

    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(.0, .0, .0);
    renderer->ResetCamera();
}



