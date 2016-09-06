#include "vtkvolume.h"
#include "vtkwindow.h"
#include "vtkslice.h"

#include <vtkRenderer.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkImageData.h>
#include <vtkProperty.h>
#include <vtkPlaneSource.h>
#include <vtkMatrix4x4.h>

VTKVolume::VTKVolume()
{
    data = vtkSmartPointer<vtkDICOMImageReader>::New();
    volume = vtkSmartPointer<vtkVolume>::New();
    volumeRenderer = vtkSmartPointer<vtkRenderer>::New();
    plane1 = vtkSmartPointer<vtkPlaneSource>::New();
    plane2 = vtkSmartPointer<vtkPlaneSource>::New();
    plane3 = vtkSmartPointer<vtkPlaneSource>::New();
}

void VTKVolume::readData(string foldername)
{
    data->SetDirectoryName(foldername.c_str());
    data->Update();
}

void VTKVolume::createVolume()
{
    data->Update();
    vtkSmartPointer<vtkSmartVolumeMapper> volmapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    volmapper->SetInputConnection(data->GetOutputPort());
    volmapper->Update();
    volmapper->SetBlendModeToComposite();
    volume->SetMapper(volmapper);
}

void VTKVolume::render(Window *window)
{
    //type cast window to VTKWindow
    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(volumeRenderer);

    // Create transfer functions
    vtkSmartPointer<vtkColorTransferFunction> colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
    vtkSmartPointer<vtkPiecewiseFunction> opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();

    // Create the property and attach the transfer functions
    vtkSmartPointer<vtkVolumeProperty> property = vtkSmartPointer<vtkVolumeProperty>::New();
    property->SetIndependentComponents(true);
    property->SetColor(colorFun);
    property->SetScalarOpacity(opacityFun);
    property->SetInterpolationTypeToLinear();

    //setting the lighting for the volume
    property->ShadeOn();
    property->SetAmbient(0.7);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);

    volume->SetProperty(property);
    volume->Update();

    volumeRenderer->RemoveAllViewProps();
    volumeRenderer->AddActor(volume);

    plane1->SetOrigin(0.0, 0.0, 0.0);
    plane1->SetNormal(0.0, 0.0, 1.0);
    plane1->SetPoint1(200.0, 0.0, 0.0);
    plane1->SetPoint2(0.0, 200.0, 0.0);

    plane2->SetOrigin(0.0, 0.0, 0.0);
    plane2->SetNormal(0.0, 0.0, 1.0);
    plane2->SetPoint1(200.0, 0.0, 0.0);
    plane2->SetPoint2(0.0, 0.0, 200.0);

    plane3->SetOrigin(0.0, 0.0, 0.0);
    plane3->SetNormal(0.0, 0.0, 1.0);
    plane3->SetPoint1(0.0, 0.0, 200.0);
    plane3->SetPoint2(0.0, 200.0, 0.0);

    vtkPolyData* p1 = plane1->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper1->SetInputData(p1);

    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
    actor1->SetMapper(mapper1);
    volumeRenderer->AddActor(actor1);

    vtkPolyData* p2 = plane2->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2->SetInputData(p2);

    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
    actor2->SetMapper(mapper2);
    volumeRenderer->AddActor(actor2);

    vtkPolyData* p3 = plane3->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper3->SetInputData(p3);

    vtkSmartPointer<vtkActor> actor3 = vtkSmartPointer<vtkActor>::New();
    actor3->SetMapper(mapper3);
    volumeRenderer->AddActor(actor3);

    volumeRenderer->SetBackground(.0, .0, .0);
    volumeRenderer->ResetCamera();
}

void VTKVolume::updatePlane(Slice* slice, int type) {
    if(type==1) {
        plane1->SetCenter(((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(0, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(1, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(2, 3));
        plane1->Update();
    }
    else if(type==2) {
        plane2->SetCenter(((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(0, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(1, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(2, 3));
        plane2->Update();
    }
    else if(type==3) {
        plane3->SetCenter(((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(0, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(1, 3),
                          ((VTKSlice *) slice)->getSlice()->GetResliceAxes()->GetElement(2, 3));
        plane3->Update();
    }
}

