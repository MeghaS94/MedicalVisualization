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
    modifiedData = vtkSmartPointer<vtkImageData>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkMarchingContourFilter>::New();
    surface->SetNumberOfContours(1);
}

VTKSurface::VTKSurface(double isoValue_start, double isoValue_end, float r, float g, float b) : Surface(isoValue_start, isoValue_end)
{
    modifiedData = vtkSmartPointer<vtkImageData>::New();
    //could use vtk contour filter to get iso-surfaces from ranges
    //surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface = vtkSmartPointer<vtkMarchingContourFilter>::New();
    surface->SetNumberOfContours(1);
    red = r; blue = b; green =g;
}

/*void VTKSurface::readData(string foldername)
{
    reader->SetDirectoryName(foldername.c_str());
    reader->Update();
    volume->DeepCopy(reader->GetOutput());
}*/

void VTKSurface::setImageData(ImageData* data) {
    imageData = (VTKImageData*) data;
    imageData->getImageData()->GetExtent(extent);
    imageData->getImageData()->GetBounds(bounds);
}

void VTKSurface::createSurface()
{
    modifiedData->DeepCopy(imageData->getImageData());
    for(int x=extent[0];x<=extent[1];x++) {
        for(int y=extent[2];y<=extent[3];y++) {
            for(int z=extent[4];z<=extent[5];z++) {
                //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
                //float* pixel1 = static_cast<float*>(modifiedData->GetScalarPointer(x,y,z));
                float pixel2 =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
                //cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;
                if(pixel2>=isovalue_start && pixel2<=isovalue_end)
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,1.0);
                else
                    modifiedData->SetScalarComponentFromFloat(x,y,z,0,0.0);
            }
        }
    }
    surface->SetInputData(modifiedData);
    surface->ComputeNormalsOn();
    surface->SetValue(0, 0.5);
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



