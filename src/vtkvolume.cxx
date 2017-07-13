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
#include <vtkExtractVOI.h>

VTKVolume::VTKVolume()
{
    extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
    volume = vtkSmartPointer<vtkVolume>::New();
    volumeRenderer = vtkSmartPointer<vtkRenderer>::New();
    plane1 = vtkSmartPointer<vtkPlaneSource>::New();
    plane2 = vtkSmartPointer<vtkPlaneSource>::New();
    plane3 = vtkSmartPointer<vtkPlaneSource>::New();
    actor1 = vtkSmartPointer<vtkActor>::New();
    actor2 = vtkSmartPointer<vtkActor>::New();
    actor3 = vtkSmartPointer<vtkActor>::New();
    colorFun = vtkSmartPointer<vtkColorTransferFunction>::New();
    opacityFun = vtkSmartPointer<vtkPiecewiseFunction>::New();
    currentLayerTab = -1;
}

void VTKVolume::setImageData(ImageData* data) {
    imageData = (VTKImageData*) data;
    imageData->getImageData()->GetExtent(extent);
    imageData->getImageData()->GetBounds(bounds);

    //cout  << "x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << endl;
    cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;
}

void VTKVolume::setLayers(Layer* layers, int n) {
    this->layers = layers;
    numberOfLayers = n;
}

void VTKVolume::setCustomLayers(Layer* customLayers, int n) {
    this->customLayers = customLayers;
    numberOfCustomLayers = n;
}

vtkSmartPointer<vtkColorTransferFunction> VTKVolume::getColorFun() {
    return colorFun;
}

vtkSmartPointer<vtkPiecewiseFunction> VTKVolume::getOpacityFun() {
    return opacityFun;
}

void VTKVolume::createVolume()
{
    //data->Update();
    vtkSmartPointer<vtkSmartVolumeMapper> volmapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
    volmapper->SetInputData(imageData->getImageData());
    //volmapper->SetInputConnection(extractVOI->GetOutputPort());
    volmapper->Update();
    volmapper->SetBlendModeToComposite();
    volume->SetMapper(volmapper);
}

// add padding to the volume to get a closed volume
void VTKVolume::addPadding() {
    extractVOI->SetInputData(imageData->getOriginalImageData());
    int tempextent[6];
    imageData->getOriginalImageData()->GetExtent(tempextent);
    int padextent[6];
    for(int i=0; i<6; i+=2) {
        if((extent[i]-1)<tempextent[i])
            padextent[i]=tempextent[i];
        else
            padextent[i]=extent[i]-1;
    }
    for(int i=1; i<6; i+=2) {
        if((extent[i]+1)>tempextent[i])
            padextent[i]=tempextent[i];
        else
            padextent[i]=extent[i]+1;
    }
    extractVOI->SetVOI(padextent[0],padextent[1],padextent[2],padextent[3],padextent[4],padextent[5]);
    extractVOI->Update();
    imageData->setImageData(extractVOI->GetOutput());
}

void VTKVolume::updateVOI(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax) {
    extractVOI->SetInputData(imageData->getOriginalImageData());
    extractVOI->SetVOI(xmin,xmax,ymin,ymax,zmin,zmax);
    extractVOI->Update();
    imageData->setImageData(extractVOI->GetOutput());
    imageData->getImageData()->GetExtent(extent);
    imageData->getImageData()->GetBounds(bounds);
    changePlanes();
    createVolume();
    volumeRenderer->GetRenderWindow()->Render();
    cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;
    makeIntervals();
    //cout  << "x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << endl;
    cout  << "x: " << bounds[0] << "x: " << bounds[1] << " y: " << bounds[2] << " y: " << bounds[3] << " z: " << bounds[4] << " z: " << bounds[5] << endl;
    //imageData->getOriginalImageData()->GetDimensions(dims);
    //cout  << "x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << endl;
    //data->SetInputData(extractVOI->GetOutput());
    //data->Update();
}

void VTKVolume::makeIntervals()
{
    //get max and min intensity
    double range[2];
    imageData->getImageData()->GetPointData()->GetScalars()->GetRange(range);
    //works only for CT
    minIntensity = range[0] ;//- 1024;
    maxIntensity = range[1] ;//- 1024;
    //make 6 intervals
    float intervalLen = (maxIntensity - minIntensity)/6.0;

    //get max and min bounds of the grid
    //cout  << "x: " << bounds[0] << " y: " << bounds[1] << " z: " << bounds[2] << endl;
    cout  << "min intensity: " << range[0] << " max intensity: " << range[1] << endl;
    cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;

}


// Plane equations
void VTKVolume::changePlanes() {
    double xpad = (bounds[1]-bounds[0])/10.0;
    double ypad = (bounds[3]-bounds[2])/10.0;
    double zpad = (bounds[5]-bounds[4])/10.0;
    plane1->SetOrigin(bounds[0]-xpad, bounds[2]-ypad, bounds[4]-zpad);
    plane1->SetPoint1(bounds[1]+xpad, bounds[2]-ypad, bounds[4]-zpad);
    plane1->SetPoint2(bounds[0]-xpad, bounds[3]+ypad, bounds[4]-zpad);
    plane1->Update();

    plane2->SetOrigin(bounds[0]-xpad, bounds[2]-ypad, bounds[4]-zpad);
    plane2->SetPoint1(bounds[1]+xpad, bounds[2]-ypad, bounds[4]-zpad);
    plane2->SetPoint2(bounds[0]-xpad, bounds[2]-ypad, bounds[5]+zpad);
    plane2->Update();

    plane3->SetOrigin(bounds[0]-xpad, bounds[2]-ypad, bounds[4]-zpad);
    plane3->SetPoint1(bounds[0]-xpad, bounds[2]-ypad, bounds[5]+zpad);
    plane3->SetPoint2(bounds[0]-xpad, bounds[3]+ypad, bounds[4]-zpad);
    plane3->Update();

}



void VTKVolume::render(Window *window)
{
    //type cast window to VTKWindow
    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(volumeRenderer);

    // Create the property and attach the transfer functions
    vtkSmartPointer<vtkVolumeProperty> property = vtkSmartPointer<vtkVolumeProperty>::New();
    property->ShadeOff();
    property->SetInterpolationType(VTK_CUBIC_INTERPOLATION );
    property->SetIndependentComponents(true);
    property->SetColor(colorFun);
    property->SetScalarOpacity(opacityFun);
    //property->SetInterpolationTypeToLinear();

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

    changePlanes();

    vtkPolyData* p1 = plane1->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper1->SetInputData(p1);
    actor1->SetMapper(mapper1);
    volumeRenderer->AddActor(actor1);

    vtkPolyData* p2 = plane2->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2->SetInputData(p2);
    actor2->SetMapper(mapper2);
    volumeRenderer->AddActor(actor2);

    vtkPolyData* p3 = plane3->GetOutput();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper3->SetInputData(p3);
    actor3->SetMapper(mapper3);
    volumeRenderer->AddActor(actor3);

    volumeRenderer->SetBackground(.0, .0, .0);
    volumeRenderer->ResetCamera();
}

void VTKVolume::changeLayerMode(int mode) {
    currentLayerTab = mode;
}

// Assigning transfer functions
void VTKVolume::updateTransferFunctions() {
    colorFun->RemoveAllPoints();
    opacityFun->RemoveAllPoints();
    if(currentLayerTab==1) {
        colorFun->AddRGBSegment(minIntensity, 0, 0, 0, maxIntensity, 0, 0, 0);
        opacityFun->AddSegment(minIntensity, 0, maxIntensity, 0);
        for(int i=0; i<numberOfLayers; i++) {
            if(layers[i].on) {
                //opacityFun->AddSegment(layers[i].isovalueStart, 0, layers[i].isovalueEnd, 0);
                //colorFun->AddRGBSegment(layers[i].isovalueStart, 0, 0, 0, layers[i].isovalueEnd, 0, 0, 0);
                opacityFun->AddPoint(layers[i].isovalueStart-0.000001, 0);
                opacityFun->AddPoint(layers[i].isovalueEnd+0.000001, 0);
                colorFun->AddRGBPoint(layers[i].isovalueStart-0.000001, 0, 0, 0);
                colorFun->AddRGBPoint(layers[i].isovalueEnd+0.000001, 0, 0, 0);
            }
        }
        for(int i=0; i<numberOfLayers; i++) {
            if(layers[i].on) {
                colorFun->AddRGBSegment(layers[i].isovalueStart, colours[i][0][0], colours[i][0][1], colours[i][0][2],
                    layers[i].isovalueEnd, colours[i][1][0], colours[i][1][1], colours[i][1][2]);
                opacityFun->AddSegment(layers[i].isovalueStart, 1, layers[i].isovalueEnd, 1);
            }
        }
    }
    else if(currentLayerTab==0) {
        colorFun->AddRGBSegment(minIntensity, 0, 0, 0, maxIntensity, 0, 0, 0);
        opacityFun->AddSegment(minIntensity, 0, maxIntensity, 0);
        for(int i=0; i<numberOfCustomLayers; i++) {
            if(customLayers[i].on) {
                //opacityFun->AddSegment(customLayers[i].isovalueStart, 0, customLayers[i].isovalueEnd, 0);
                opacityFun->AddPoint(customLayers[i].isovalueStart-0.000001, 0);
                opacityFun->AddPoint(customLayers[i].isovalueEnd+0.000001, 0);
                colorFun->AddRGBPoint(customLayers[i].isovalueStart-0.000001, 0, 0, 0);
                colorFun->AddRGBPoint(customLayers[i].isovalueEnd+0.000001, 0, 0, 0);
            }
        }
        for(int i=0; i<numberOfCustomLayers; i++) {
            if(customLayers[i].on) {
                colorFun->AddRGBSegment(customLayers[i].isovalueStart, colours[i][0][0], colours[i][0][1], colours[i][0][2],
                    customLayers[i].isovalueEnd, colours[i][1][0], colours[i][1][1], colours[i][1][2]);
                opacityFun->AddSegment(customLayers[i].isovalueStart, 1, customLayers[i].isovalueEnd, 1);
            }
        }
    }
    volumeRenderer->GetRenderWindow()->Render();
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
    volumeRenderer->GetRenderWindow()->Render();
}

void VTKVolume::axialPlane(bool visibility) {
    if(visibility)
        actor1->VisibilityOn();
    else
        actor1->VisibilityOff();
    volumeRenderer->GetRenderWindow()->Render();
}

void VTKVolume::coronalPlane(bool visibility) {
    if(visibility)
        actor2->VisibilityOn();
    else
        actor2->VisibilityOff();
    volumeRenderer->GetRenderWindow()->Render();
}

void VTKVolume::sagittalPlane(bool visibility) {
    if(visibility)
        actor3->VisibilityOn();
    else
        actor3->VisibilityOff();
    volumeRenderer->GetRenderWindow()->Render();
}

