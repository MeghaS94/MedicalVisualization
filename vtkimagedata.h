#ifndef VTKIMAGEDATA_H
#define VTKIMAGEDATA_H

#include <vtkSmartPointer.h>
//#include <vtkGDCMImageReader.h>
#include <vtkImageData.h>
#include <imagedata.h>

class VTKImageData : public ImageData
{
public:
    VTKImageData();
    void loadData(string foldername);
    vtkSmartPointer<vtkImageData> getImageData();
    vtkSmartPointer<vtkImageData> getOriginalImageData();
    void setImageData(vtkSmartPointer<vtkImageData> data);
    int* getExtent();
    vector<double> Spacing();

private:
    vtkSmartPointer<vtkImageData> originalImageData;
    vtkSmartPointer<vtkImageData> imageData;
};

#endif // VTKIMAGEDATA_H
