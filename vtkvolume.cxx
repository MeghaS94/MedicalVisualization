#include "vtkvolume.h"
#include "vtkwindow.h"
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
   volumeRenderer->AddActor(volume);


   /*double bounds[6];
   data->GetOutput()->GetBounds(bounds);

   vtkSmartPointer<vtkPlane> plane =
     vtkSmartPointer<vtkPlane>::New();
   plane->SetOrigin((bounds[1] + bounds[0]) / 2.0,
                    (bounds[3] + bounds[2]) / 2.0,
                    bounds[4]);
   plane->SetNormal(0,0,1);

   // Create cutter
   double high = plane->EvaluateFunction((bounds[1] + bounds[0]) / 2.0,
                                         (bounds[3] + bounds[2]) / 2.0,
                                         bounds[5]);

   vtkSmartPointer<vtkCutter> cutter =
     vtkSmartPointer<vtkCutter>::New();
   cutter->SetInputConnection(data->GetOutputPort());
   cutter->SetCutFunction(plane);
   cutter->GenerateValues(
     10,
     .99,
     .99 * high);

   vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
     vtkSmartPointer<vtkPolyDataMapper>::New();
   cutterMapper->SetInputConnection( cutter->GetOutputPort());
   cutterMapper->ScalarVisibilityOff();

   // Create cut actor
   vtkSmartPointer<vtkActor> cutterActor =
     vtkSmartPointer<vtkActor>::New();
   cutterActor->GetProperty()->SetColor(1.0,1.0,0);
   cutterActor->GetProperty()->SetLineWidth(2);
   cutterActor->SetMapper(cutterMapper);
   volumeRenderer->AddActor(cutterActor);*/

   // Create a plane
     vtkSmartPointer<vtkPlaneSource> planeSource =
       vtkSmartPointer<vtkPlaneSource>::New();
     planeSource->SetCenter(1.0, 0.0, 0.0);
     planeSource->SetNormal(1.0, 0.0, 1.0);
     planeSource->Update();

     vtkPolyData* plane = planeSource->GetOutput();

     // Create a mapper and actor
     vtkSmartPointer<vtkPolyDataMapper> mapper =
       vtkSmartPointer<vtkPolyDataMapper>::New();
   #if VTK_MAJOR_VERSION <= 5
     mapper->SetInput(plane);
   #else
     mapper->SetInputData(plane);
   #endif

     vtkSmartPointer<vtkActor> actor =
       vtkSmartPointer<vtkActor>::New();
     actor->SetMapper(mapper);

   volumeRenderer->SetBackground(.0, .0, .0);
   volumeRenderer->ResetCamera();

}
