#include "vtkvolume.h"
#include "vtkwindow.h"
#include <vtkRenderer.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartVolumeMapper.h>


VTKVolume::VTKVolume()
{
    data = vtkSmartPointer<vtkDICOMImageReader>::New();
    volume = vtkSmartPointer<vtkVolume>::New();
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
   vtkSmartPointer<vtkRenderer> volumeRenderer = vtkSmartPointer<vtkRenderer>::New();

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

   //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
   //renderWindowInteractor->SetRenderWindow (volumeRenderer->GetRenderWindow());
   //vtkSmartPointer<customMouseInteractorStyle1> style = vtkSmartPointer<customMouseInteractorStyle1>::New();
   //renderWindowInteractor->SetInteractorStyle(style);
   //style->setRenderer(this);
   //renderWindowInteractor->Initialize();
   //renderWindowInteractor->Start();

   volumeRenderer->RemoveAllViewProps();
   volumeRenderer->AddViewProp(volume);
   volumeRenderer->SetBackground(.0, .0, .0);
   volumeRenderer->ResetCamera();

}
