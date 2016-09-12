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
#include <vtkPointData.h>

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

void VTKVolume::makeIntervals()
{
    //get max and min intensity
    double range[2];
    data->GetOutput()->GetPointData()->GetScalars()->GetRange(range);
    minIntensity = range[0];
    maxIntensity = range[1];
    //make 6 intervals
    int intervalLen = (maxIntensity - minIntensity+1)/6;

    //get max and min bounds of the grid
    double bounds[6];
    data->GetOutput()->GetBounds(bounds);
    std::cout  << "xmin: " << bounds[0] << " "
                 << "xmax: " << bounds[1] << std::endl
                 << "ymin: " << bounds[2] << " "
                 << "ymax: " << bounds[3] << std::endl
                 << "zmin: " << bounds[4] << " "
                 << "zmax: " << bounds[5] << std::endl;

    voxel_count = 0; //count of the total number of voxels
    for(int x=bounds[0];x<bounds[1];x++)
    {
        for(int y=bounds[2];y<bounds[3];y++)
        {
            for(int z=bounds[4];z<20;z++) //what to do about this out of range error?
            {
                //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
                float pixel =  (data->GetOutput()->GetScalarComponentAsFloat(x,y,z,0));
                int bin = pixel/intervalLen;
                Map[bin] +=1;
                voxel_count +=1;
            }
        }
    }
    //return Map;
}

void VTKVolume::render(Window *window)
{
    //type cast window to VTKWindow
    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(volumeRenderer);

    vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    volumeMapper->SetInputConnection(data->GetOutputPort()) ;


    // Create transfer functions
    vtkSmartPointer<vtkColorTransferFunction> colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
    vtkSmartPointer<vtkPiecewiseFunction> opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();

    // Create the property and attach the transfer functions
    vtkSmartPointer<vtkVolumeProperty> property = vtkSmartPointer<vtkVolumeProperty>::New();
    property->ShadeOff();
    property->SetInterpolationType(VTK_CUBIC_INTERPOLATION );
    property->SetIndependentComponents(true);
    property->SetColor(colorFun);
    property->SetScalarOpacity(opacityFun);
    //property->SetInterpolationTypeToLinear();

    //-------------------------Transfer Functions-------------------------
    //float red = 0.93; float green = 0.25; float blue = 0.30; float opacity = 1.0;

      int intervalLen = (maxIntensity - minIntensity+1)/6;
      cout << "Intensity range    " << "Count  " << endl;
      cout << "--------------------------------" << endl;
      //Assigning colors to the volume R,G,B.
      colorFun->AddRGBPoint( minIntensity, 0.0, 0.0, 0.0 );                   cout << minIntensity << " to " << minIntensity +intervalLen << "        " << Map[minIntensity] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen, 0.6, 0.6, 0.6 );       cout << minIntensity+intervalLen << " to " << minIntensity +2*intervalLen << "       " <<Map[minIntensity+1] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*2 ,  0.7, 0.7, 0.7 );   cout << minIntensity+2*intervalLen << " to " << minIntensity +3*intervalLen<< "      "  <<Map[minIntensity+2] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*3,  0.8, 0.0, 0.0 );    cout << minIntensity+3*intervalLen << " to " << minIntensity +4*intervalLen<< "      "  <<Map[minIntensity+3] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*4,  0.0, 0.7, 0.0 );    cout << minIntensity+4*intervalLen << " to " << minIntensity +5*intervalLen<< "      "  <<Map[minIntensity+4] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*5,  0.0, 0.0, 0.6 );    cout << minIntensity+5*intervalLen << " to " << minIntensity +6*intervalLen<< "      "  <<Map[minIntensity+5] << endl;
      colorFun->AddRGBPoint( maxIntensity,  0.0, 0.0, 0.6 );

      //colorFun->AddRGBPoint( 80 , 0.5, 0.5, 0.5 );
      //colorFun->AddRGBPoint( 90 , 0.7, 0.7, 0.7);

      //ratio of number of pixels having that intensity/total num of voxels -> to determine opacity
      opacityFun->AddPoint(minIntensity,0 );
      opacityFun->AddPoint(minIntensity+intervalLen, 2*Map[minIntensity+1] / voxel_count );
      opacityFun->AddPoint(minIntensity+2*intervalLen, 2*Map[minIntensity+2] / voxel_count );
      opacityFun->AddPoint(minIntensity+3*intervalLen, 2*Map[minIntensity+3] / voxel_count  );
      opacityFun->AddPoint(minIntensity+4*intervalLen, 2*Map[minIntensity+4] / voxel_count );
      opacityFun->AddPoint(minIntensity+5*intervalLen, 2*Map[minIntensity+5] / voxel_count );
      opacityFun->AddPoint(maxIntensity, 0.3 );
      //opacityFun->AddPoint(80, 0.03 );

    //-------------------------------------------------------------------
    //setting the lighting for the volume
    property->ShadeOn();
    property->SetAmbient(0.7);
    property->SetDiffuse(0.9);
    property->SetSpecular(0.2);
    property->SetSpecularPower(10.0);
    property->SetScalarOpacityUnitDistance(0.8919);

    //std::cout << range[0] << ", " << range[1] << endl;
    //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarPointer(0,0,0));
    //cout << pixel[0] << endl;

    volume->SetProperty(property);
    volume->SetMapper(volumeMapper);
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


