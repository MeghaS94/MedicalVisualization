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
}

/*void VTKVolume::readData(string foldername)
{
    data->SetDirectoryName(foldername.c_str());
    data->Update();
    imageData = data->GetOutput();
    imageData->GetDimensions(dims);
    imageData->GetBounds(bounds);
    cout  << "x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << endl;
    cout  << "x: " << bounds[0] << "x: " << bounds[1] << " y: " << bounds[2] << " y: " << bounds[3] << " z: " << bounds[4] << " z: " << bounds[5] << endl;
}*/

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
    //cout  << "x: " << bounds[0] << "x: " << bounds[1] << " y: " << bounds[2] << " y: " << bounds[3] << " z: " << bounds[4] << " z: " << bounds[5] << endl;
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
    minIntensity = range[0];
    maxIntensity = range[1];
    //make 6 intervals
    float intervalLen = (maxIntensity - minIntensity)/6.0;

    //get max and min bounds of the grid
    //cout  << "x: " << bounds[0] << " y: " << bounds[1] << " z: " << bounds[2] << endl;
    cout  << "min intensity: " << range[0] << " max intensity: " << range[1] << endl;
    cout  << "x: " << extent[0] << "x: " << extent[1] << " y: " << extent[2] << " y: " << extent[3] << " z: " << extent[4] << " z: " << extent[5] << endl;

    //voi extents - x-> 100, 400 | 250, 511
    //y-> 50, 250 | 50, 210
    //z -> 50, 200 | 0, 249

    int y =  ( extent[3] + extent[2] )/2.0;
    int z = ( extent[5] + extent[4] )/2.0;
    int count = 0;
    float min, max;
    min = (imageData->getImageData()->GetScalarComponentAsFloat(100,y,z,0));
    max = (imageData->getImageData()->GetScalarComponentAsFloat(100,y,z,0));
    for(int x=extent[0];x<=extent[1];x++)
    {
        //for(int y=extent[2];y<=extent[3];y++)
        //{
          //  for(int z=extent[4];z<=extent[5];z++)
            //{
                //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
                float pixel =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
                cout << "Intensity along a ray : "<<pixel << endl;
                if (pixel < min)
                        {
                       min = pixel;
                }
                if (pixel > max)
                {
                    max = pixel;
                }
                //int count = 0;

            //}
        //}
    }

   vector< vector<float> >  intervals;
   vector<int> counts;
   float num_of_intervals = (max - min)/10.0;
   float temp = min;
   for(int i=0;i<num_of_intervals;i++)
        {
        vector<float> interval;
        interval.push_back(temp);
        interval.push_back(temp+ 10.0);
        temp = temp +10.0;
        intervals.push_back(interval);
        counts.push_back(0);
         }


   for(int x=extent[0];x<=extent[1];x++)
   {
       //for(int y=extent[2];y<=extent[3];y++)
       //{
         //  for(int z=extent[4];z<=extent[5];z++)
           //{
               //double* pixel =  static_cast<double*>(data->GetOutput()->GetScalarComponentAsFloat(x,y,z,1));
               float pixel =  (imageData->getImageData()->GetScalarComponentAsFloat(x,y,z,0));
               //cout << "Intensity along a ray : "<<pixel << endl;
               for (int j=0;j< intervals.size();j++)
               {
                   if (intervals[j][0] < pixel &&  intervals[j][1] > pixel )
                   {
                       counts[j] += 1;
                       break;
                   }
               }


           //}
       //}
   }

   cout << "print histogram" << endl;
   for (int j=0;j< intervals.size();j++)
   {
       cout << intervals[j][0] << " - " << intervals[j][1] << " -> " << counts[j] << endl;
   }


}

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

    //-------------------------Transfer Functions-------------------------
    //float red = 0.93; float green = 0.25; float blue = 0.30; float opacity = 1.0;

      //float intervalLen = (maxIntensity - minIntensity)/6.0;
      //cout << "Intensity range    " << "Count  " << endl;
      //cout << "--------------------------------" << endl;
      //Assigning colors to the volume R,G,B.
      /*colorFun->AddRGBPoint( minIntensity, 0.0, 0.0, 0.0 );                   cout << minIntensity << " to " << minIntensity +intervalLen << "        " << Map[0] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen, 0.6, 0.6, 0 );       cout << minIntensity+intervalLen << " to " << minIntensity +2*intervalLen << "       " <<Map[1] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*2 ,  0, 0.7, 0.7 );   cout << minIntensity+2*intervalLen << " to " << minIntensity +3*intervalLen<< "      "  <<Map[2] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*3,  0.8, 0.0, 0.0 );    cout << minIntensity+3*intervalLen << " to " << minIntensity +4*intervalLen<< "      "  <<Map[3] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*4,  0.0, 0.7, 0.0 );    cout << minIntensity+4*intervalLen << " to " << minIntensity +5*intervalLen<< "      "  <<Map[4] << endl;
      colorFun->AddRGBPoint( minIntensity+intervalLen*5,  0.0, 0.0, 0.6 );    cout << minIntensity+5*intervalLen << " to " << minIntensity +6*intervalLen<< "      "  <<Map[5] << endl;
      colorFun->AddRGBPoint( maxIntensity,  0.0, 0.0, 0.6 );

      //colorFun->AddRGBPoint( 80 , 0.5, 0.5, 0.5 );
      //colorFun->AddRGBPoint( 90 , 0.7, 0.7, 0.7);
      //for(int i=0; i<1000; i+=10)
      //    printf("%d %f %f %f\n", i, colorFun->GetRedValue(i), colorFun->GetGreenValue(i), colorFun->GetBlueValue(i));

      //ratio of number of pixels having that intensity/total num of voxels -> to determine opacity
      opacityFun->AddPoint(minIntensity,0 );
      opacityFun->AddPoint(minIntensity+intervalLen, 2*Map[1] / voxel_count );
      opacityFun->AddPoint(minIntensity+2*intervalLen, 2*Map[2] / voxel_count );
      opacityFun->AddPoint(minIntensity+3*intervalLen, 2*Map[3] / voxel_count  );
      opacityFun->AddPoint(minIntensity+4*intervalLen, 2*Map[4] / voxel_count );
      opacityFun->AddPoint(minIntensity+5*intervalLen, 2*Map[5] / voxel_count );
      opacityFun->AddPoint(maxIntensity, 0.3 );
      //opacityFun->AddPoint(80, 0.03 );*/

    //-------------------------------------------------------------------
    //setting the lighting for the volume

    for(int i=0; i<numberOfLayers; i++) {
        colorFun->AddRGBSegment(layers[i].isovalueStart, colours[i][0][0], colours[i][0][1], colours[i][0][2],
                layers[i].isovalueEnd, colours[i][1][0], colours[i][1][1], colours[i][1][2]);
    }

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

void VTKVolume::updateTransferFunctions() {
    //colorFun->RemoveAllPoints();
    //opacityFun->RemoveAllPoints();
    //opacityFun->AddSegment(minIntensity, 0, maxIntensity, 0);
    for(int i=0; i<numberOfLayers; i++) {
        if(!layers[i].on) {
            opacityFun->AddSegment(layers[i].isovalueStart, 0, layers[i].isovalueEnd, 0);
        }
    }
    for(int i=0; i<numberOfLayers; i++) {
        if(layers[i].on) {
            colorFun->AddRGBSegment(layers[i].isovalueStart, colours[i][0][0], colours[i][0][1], colours[i][0][2],
                layers[i].isovalueEnd, colours[i][1][0], colours[i][1][1], colours[i][1][2]);
            opacityFun->AddSegment(layers[i].isovalueStart, 1, layers[i].isovalueEnd, 1);
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

