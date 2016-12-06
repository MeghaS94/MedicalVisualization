#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformation.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPolyData.h>
#include <vtkVersion.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkIntArray.h>
#include <vtkContextView.h>
#include <vtkContextActor.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>

#include <set>
#include "vtkslice.h"
#include "window.h"
#include "vtkwindow.h"

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

VTKSlice::VTKSlice(int type, Controller* c) : Slice(type)
{
    slice = vtkSmartPointer<vtkImageReslice>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    controller = c;
    actor = vtkSmartPointer<vtkImageActor>::New();
}

vtkSmartPointer<vtkImageReslice> VTKSlice::getSlice() {
    return slice;
}

vtkSmartPointer<vtkImageData> VTKSlice::getData() {
    return imageData->getImageData();
}

Controller* VTKSlice::getController() {
    return controller;
}

/*void VTKSlice::readData(string foldername) {
    vtkSmartPointer<vtkDICOMImageReader> temp_data = vtkSmartPointer<vtkDICOMImageReader>::New();
    temp_data->SetDirectoryName(foldername.c_str());
    temp_data->Update();
    data = temp_data;
    data->SetDataByteOrderToLittleEndian();
    data->UpdateWholeExtent();
    data->Update();
}*/

void VTKSlice::setImageDataVolume(ImageData* data, Volume* v) {
    imageData = (VTKImageData*) data;
    volume = (VTKVolume*) v;
}

void VTKSlice::createSlice() {
    double center[3];
    imageData->getImageData()->GetCenter(center);

    // Matrices for axial, coronal, sagittal, oblique view orientations
    static double axialElements[16] = {
             1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1 };

    static double coronalElements[16] = {
             1, 0, 0, 0,
             0, 0, 1, 0,
             0,-1, 0, 0,
             0, 0, 0, 1 };

    static double sagittalElements[16] = {
             0, 0,-1, 0,
             1, 0, 0, 0,
             0,-1, 0, 0,
             0, 0, 0, 1 };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
    if(type==1)
        resliceAxes->DeepCopy(axialElements);
    else if(type==2)
        resliceAxes->DeepCopy(coronalElements);
    else if(type==3)
        resliceAxes->DeepCopy(sagittalElements);
    // Set the point through which to slice
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    slice->SetInputData(imageData->getImageData());
    slice->SetOutputDimensionality(2);
    slice->SetResliceAxes(resliceAxes);
    slice->SetInterpolationModeToLinear();
}

void VTKSlice::updateSlice() {
    double center[3];
    imageData->getImageData()->GetCenter(center);
    slice->SetInputData(imageData->getImageData());
    vtkMatrix4x4 *matrix = slice->GetResliceAxes();
    matrix->SetElement(0, 3, center[0]);
    matrix->SetElement(1, 3, center[1]);
    matrix->SetElement(2, 3, center[2]);
    slice->Update();
    renderer->GetRenderWindow()->Render();
}

void VTKSlice::updateTransferFunction() {
    // Map the image through the lookup table
    vtkSmartPointer<vtkImageMapToColors> color =
      vtkSmartPointer<vtkImageMapToColors>::New();
    color->SetLookupTable(volume->getColorFun());
    color->SetInputConnection(slice->GetOutputPort());
    actor->GetMapper()->SetInputConnection(color->GetOutputPort());
    renderer->GetRenderWindow()->Render();
}

double VTKSlice::getPosition() {
    if(type==1)
        return (slice->GetResliceAxes()->GetElement(2, 3)-getData()->GetBounds()[4])/getData()->GetSpacing()[2];
    else if(type==2)
        return (slice->GetResliceAxes()->GetElement(1, 3)-getData()->GetBounds()[2])/getData()->GetSpacing()[1];
    else
        return (slice->GetResliceAxes()->GetElement(0, 3)-getData()->GetBounds()[0])/getData()->GetSpacing()[0];

}

int VTKSlice::getType()
{
    return type;
}

void VTKSlice::createHistogram() {
    vector<double> I;
    I = intensity();
    cout << I.size() << endl;
    set<double> distinct_intensities(I.begin(), I.end());
    cout << distinct_intensities.size() << endl;

    set<double>::iterator it;

    vector<int> data;

    cout << "set" << endl;
    for (it =distinct_intensities.begin(); it!= distinct_intensities.end();it++)
    {
      //cout << *it << endl;
      int value = *it;
      int countI = count(I.begin(), I.end(), value);
      data.push_back(countI);
    }
    VTK_CREATE(vtkContextView, view);
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetSize(400, 300);
    VTK_CREATE(vtkChartXY, chart);
    view->GetScene()->AddItem(chart);

    // Create a table with some points in it...
    VTK_CREATE(vtkTable, table);

    VTK_CREATE(vtkIntArray, values);
    values->SetName("Value");
    table->AddColumn(values);

    VTK_CREATE(vtkIntArray, arr);
    arr->SetName("Freq");
    table->AddColumn(arr);
    table->SetNumberOfRows(distinct_intensities.size());
    for (int i = 0; i < distinct_intensities.size(); i++)
    {
      table->SetValue(i,0,i+1);
      table->SetValue(i,1,data[i]);
    }

    // Add multiple line plots, setting the colors etc
    vtkPlot *line = 0;

    line = chart->AddPlot(vtkChart::BAR);
  #if VTK_MAJOR_VERSION <= 5
    line->SetInput(table, 0, 1);
  #else
    line->SetInputData(table, 0, 1);
  #endif
    line->SetColor(0, 255, 0, 255);
    //Finally render the scene and compare the image to a reference image
    view->GetRenderWindow()->SetMultiSamples(0);
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();
}

vector<double> VTKSlice::intensity()
{

    cout << "slice size : " << slice->GetResliceAxes()->GetElement(2, 3)-getData()->GetBounds()[0] << ", " <<
            slice->GetResliceAxes()->GetElement(2, 3)-getData()->GetBounds()[1]<< endl;
    vtkSmartPointer<vtkImageData> sliceData;
    sliceData = vtkSmartPointer<vtkImageData>::New();
    sliceData = slice->GetOutput();
    int* dims = sliceData->GetDimensions();
    double scalarRange[2];
    sliceData->GetScalarRange(scalarRange);
    cout << scalarRange[0] << "< " << scalarRange[1] << endl;
      // int dims[3]; // can't do this
    vector<double> intensities;
    std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;
    for (int z = 0; z < dims[2]; z++)
        {
        for (int y = 0; y < dims[1]; y++)
          {
          for (int x = 0; x < dims[0]; x++)
            {
              double color1;
              color1 = sliceData->GetScalarComponentAsDouble(x,y,z, 0);
              intensities.push_back(color1);
              //cout << color1 << endl;
            //double* pixel = static_cast<double*>(sliceData->GetScalarPointer(x,y,z));
            //cout << pixel[0] << ", " << pixel[1] << ", " << pixel[2] << endl;
            }
          }
        }
    return intensities;

}

void VTKSlice::render(Window* window) {
    // Create a greyscale lookup table
    vtkSmartPointer<vtkLookupTable> table =
      vtkSmartPointer<vtkLookupTable>::New();
    double min = imageData->getImageData()->GetScalarRange()[0];
    double max = imageData->getImageData()->GetScalarRange()[1];
    table->SetRange(min, max); // image intensity range
    table->SetValueRange(0.0, 1.0); // from black to white
    table->SetSaturationRange(0.0, 0.0); // no color saturation
    table->SetRampToLinear();
    table->Build();

    // Map the image through the lookup table
    vtkSmartPointer<vtkImageMapToColors> color =
      vtkSmartPointer<vtkImageMapToColors>::New();
    color->SetLookupTable(volume->getColorFun());
    color->SetInputConnection(slice->GetOutputPort());

    actor->GetMapper()->SetInputConnection(color->GetOutputPort());

    renderer->AddActor(actor);


    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(.0, .0, .0);

    // Set up the interaction
    vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
    vtkSmartPointer<QVTKInteractor> interactor = vtkSmartPointer<QVTKInteractor>::New();
    interactor->SetInteractorStyle(imageStyle);
    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->SetInteractor(interactor);

    vtkSmartPointer<vtkSliceInteractionCallback> callback = vtkSmartPointer<vtkSliceInteractionCallback>::New();
    callback->SetSlice(this);
    callback->SetInteractor(interactor);

    imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
    imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
    imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);

    interactor->Initialize();
}

vtkSliceInteractionCallback::vtkSliceInteractionCallback()
{
    this->slicing = 0;
    this->slice = 0;
    this->interactor = 0;
}

void vtkSliceInteractionCallback::SetSlice(VTKSlice* slice)
{
    this->slice = slice;
}

VTKSlice* vtkSliceInteractionCallback::GetSlice()
{
    return this->slice;
}

void vtkSliceInteractionCallback::SetInteractor(vtkRenderWindowInteractor* interactor)
{
    this->interactor = interactor;
}

vtkRenderWindowInteractor* vtkSliceInteractionCallback::GetInteractor()
{
    return this->interactor;
}

void vtkSliceInteractionCallback::Execute(vtkObject *, unsigned long event, void *) VTK_OVERRIDE
{
    int lastPos[2];
    interactor->GetLastEventPosition(lastPos);
    int currPos[2];
    interactor->GetEventPosition(currPos);

    if (event == vtkCommand::LeftButtonPressEvent)
        this->slicing = 1;
    else if (event == vtkCommand::LeftButtonReleaseEvent)
        this->slicing = 0;
    else if (event == vtkCommand::MouseMoveEvent)
    {
        if (this->slicing)
        {
            // Increment slice position by deltaY of mouse
            int deltaY = lastPos[1] - currPos[1];
            slice->getSlice()->Update();
            double sliceSpacing = slice->getSlice()->GetOutput()->GetSpacing()[0];
            double bounds[6];
            slice->getData()->GetBounds(bounds);
            vtkMatrix4x4 *matrix = slice->getSlice()->GetResliceAxes();
            // move the center point that we are slicing through
            double point[4];
            double center[4];
            point[0] = 0.0;
            point[1] = 0.0;
            point[2] = sliceSpacing * deltaY;
            //point[2] = deltaY;
            point[3] = 1.0;
            matrix->MultiplyPoint(point, center);
            if(center[0]<bounds[0])
                center[0]=bounds[0];
            if(center[0]>bounds[1])
                center[0]=bounds[1];
            if(center[1]<bounds[2])
                center[1]=bounds[2];
            if(center[1]>bounds[3])
                center[1]=bounds[3];
            if(center[2]<bounds[4])
                center[2]=bounds[4];
            if(center[2]>bounds[5])
                center[2]=bounds[5];
            matrix->SetElement(0, 3, center[0]);
            matrix->SetElement(1, 3, center[1]);
            matrix->SetElement(2, 3, center[2]);
            interactor->Render();
            slice->getController()->updateVolumePlanes();
        }
        else
        {
            vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(interactor->GetInteractorStyle());
            if (style)
                style->OnMouseMove();
        }
    }
}

