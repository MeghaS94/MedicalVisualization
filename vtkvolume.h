#ifndef VTKVOLUME_H
#define VTKVOLUME_H

#include <QWidget>
#include "window.h"
#include "volume.h"
#include <vtkVolume.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <string>
#include <vtkPlaneSource.h>

#include "slice.h"

using namespace std;

class VTKVolume : public Volume
{
private :
    vtkSmartPointer<vtkVolume> volume;
    vtkSmartPointer<vtkDICOMImageReader> data;
    vtkSmartPointer<vtkRenderer> volumeRenderer;
    vtkSmartPointer<vtkPlaneSource> plane1;
    vtkSmartPointer<vtkPlaneSource> plane2;
    vtkSmartPointer<vtkPlaneSource> plane3;

public:
    VTKVolume();
    void readData(string foldername);
    void createVolume();
    void render(Window *window);
    void updatePlane(Slice* slice, int type);

};

#endif // VTKVOLUME_H
