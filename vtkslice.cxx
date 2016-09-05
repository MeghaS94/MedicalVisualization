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

#include "vtkslice.h"
#include "window.h"
#include "vtkwindow.h"

VTKSlice::VTKSlice(int type) : Slice(type)
{
    data = vtkSmartPointer<vtkImageReader2>::New();
    slice = vtkSmartPointer<vtkImageReslice>::New();
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
    table->SetRange(0, 2000); // image intensity range
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
    renderer->ResetCamera();
}
