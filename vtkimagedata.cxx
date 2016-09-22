#include <vtkDICOMImageReader.h>
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
    vtkSmartPointer<vtkDICOMImageReader> data = vtkSmartPointer<vtkDICOMImageReader>::New();
    data->SetDirectoryName(foldername.c_str());
    data->Update();
    imageData = data->GetOutput();
    originalImageData = data->GetOutput();
}

int* VTKImageData::getExtent() {
    return originalImageData->GetExtent();
}
