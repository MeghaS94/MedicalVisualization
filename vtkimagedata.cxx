#include <vtkDICOMImageReader.h>
//#include <vtkGDCMImageReader.h>
#include <vtkDirectory.h>
#include <vtkStringArray.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include "vtkimagedata.h"

VTKImageData::VTKImageData()
{
    imageData = vtkSmartPointer<vtkImageData>::New();
    originalImageData = vtkSmartPointer<vtkImageData>::New();
}

vtkSmartPointer<vtkImageData> VTKImageData::getImageData() {
    return imageData;
}

vtkSmartPointer<vtkImageData> VTKImageData::getOriginalImageData() {
    return originalImageData;
}

void VTKImageData::setImageData(vtkSmartPointer<vtkImageData> data) {
    imageData = data;
}

void VTKImageData::loadData(string foldername) {
    vtkSmartPointer<vtkDICOMImageReader> data = vtkDICOMImageReader::New();
    data->SetDirectoryName(foldername.c_str());
    data->Update();
    imageData = data->GetOutput();
    originalImageData = data->GetOutput();

    //double spacing2[3];
    //originalImageData->GetSpacing(spacing2);
    //cout << "spacing : " << spacing2[0] << " , " << spacing2[1] << ", " << spacing2[2] << endl;
}

vector<double> VTKImageData::Spacing()
{
    double spacing[3];
    imageData->GetSpacing(spacing);
    cout << "spacing : " << spacing[0] << " , " << spacing[1] << ", " << spacing[2] << endl;
    vector<double> pixel_spacing;
    pixel_spacing.push_back(spacing[0]);   pixel_spacing.push_back(spacing[1]);   pixel_spacing.push_back(spacing[2]);
    return pixel_spacing;
}


int* VTKImageData::getExtent() {
    return originalImageData->GetExtent();
}

double* VTKImageData::intensity(int x, int y, int z)
{
    double* pixel = static_cast<double*>(originalImageData->GetScalarPointer(x,y,z));
    return pixel;
}

double* VTKImageData::getRange() {
    return originalImageData->GetPointData()->GetScalars()->GetRange();
}
