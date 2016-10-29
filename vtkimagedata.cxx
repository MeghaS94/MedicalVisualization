#include <vtkDICOMImageReader.h>
//#include <vtkGDCMImageReader.h>
#include <vtkDirectory.h>
#include <vtkStringArray.h>
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
    /*vtkGDCMImageReader* data = vtkGDCMImageReader::New();
    printf("DOne\n");
    vtkSmartPointer<vtkDirectory> dir = vtkSmartPointer<vtkDirectory>::New();
    vtkStringArray* arr = vtkStringArray::New();
    printf("DOne\n");
    dir->Open(foldername.c_str());
    cout << dir->GetFiles()->GetNumberOfValues() << endl;
    for(int i=0; i<dir->GetFiles()->GetNumberOfValues(); i++) {
        cout << dir->GetFiles()->GetValue(i) << endl;
        if(i>1)
            arr->InsertNextValue(dir->GetFiles()->GetValue(i));
    }
    printf("DOne\n");
    data->SetFileNames(arr);

    printf("DOne\n");
    data->FileLowerLeftOn();*/
    vtkSmartPointer<vtkDICOMImageReader> data = vtkDICOMImageReader::New();
    data->SetDirectoryName(foldername.c_str());
    data->Update();
    imageData = data->GetOutput();
    originalImageData = data->GetOutput();
}

int* VTKImageData::getExtent() {
    return originalImageData->GetExtent();
}
