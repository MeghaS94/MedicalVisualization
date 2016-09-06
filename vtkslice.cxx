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

#include "vtkslice.h"
#include "window.h"
#include "vtkwindow.h"

VTKSlice::VTKSlice(int type) : Slice(type)
{
    data = vtkSmartPointer<vtkImageReader2>::New();
    slice = vtkSmartPointer<vtkImageReslice>::New();
}

vtkSmartPointer<vtkImageReslice> VTKSlice::getSlice() {
    return slice;
}

vtkSmartPointer<vtkImageReader2> VTKSlice::getData() {
    return data;
}

void VTKSlice::readData(string foldername) {
    vtkSmartPointer<vtkDICOMImageReader> temp_data = vtkSmartPointer<vtkDICOMImageReader>::New();
    temp_data->SetDirectoryName(foldername.c_str());
    temp_data->Update();
    data = temp_data;
    data->SetDataByteOrderToLittleEndian();
    data->UpdateWholeExtent();
    data->Update();
}

void VTKSlice::createSlice() {
    int extent[6];
    double spacing[3];
    double origin[3];

    data->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
    data->GetOutput()->GetSpacing(spacing);
    data->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

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

    slice->SetInputConnection(data->GetOutputPort());
    slice->SetOutputDimensionality(2);
    slice->SetResliceAxes(resliceAxes);
    slice->SetInterpolationModeToLinear();
}

void VTKSlice::render(Window* window ) {
    // Create a greyscale lookup table
    vtkSmartPointer<vtkLookupTable> table =
      vtkSmartPointer<vtkLookupTable>::New();
    double min = data->GetOutput()->GetScalarRange()[0];
    double max = data->GetOutput()->GetScalarRange()[1];
    table->SetRange(min, max); // image intensity range
    table->SetValueRange(0.0, 1.0); // from black to white
    table->SetSaturationRange(0.0, 0.0); // no color saturation
    table->SetRampToLinear();
    table->Build();

    // Map the image through the lookup table
    vtkSmartPointer<vtkImageMapToColors> color =
      vtkSmartPointer<vtkImageMapToColors>::New();
    color->SetLookupTable(table);
    color->SetInputConnection(slice->GetOutputPort());

    // Display the image
    vtkSmartPointer<vtkImageActor> actor =
      vtkSmartPointer<vtkImageActor>::New();
    actor->GetMapper()->SetInputConnection(color->GetOutputPort());

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    ((VTKWindow*)window)->getWidget()->GetRenderWindow()->AddRenderer(renderer);
    renderer->SetBackground(.0, .0, .0);

    // Set up the interaction
    vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
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
            double sliceSpacing = slice->getSlice()->GetOutput()->GetSpacing()[2];
            double bounds[6];
            slice->getData()->GetOutput()->GetBounds(bounds);
            vtkMatrix4x4 *matrix = slice->getSlice()->GetResliceAxes();
            // move the center point that we are slicing through
            double point[4];
            double center[4];
            point[0] = 0.0;
            point[1] = 0.0;
            //point[2] = sliceSpacing * deltaY;
            point[2] = deltaY;
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
        }
        else
        {
            vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(interactor->GetInteractorStyle());
            if (style)
                style->OnMouseMove();
        }
    }
}

