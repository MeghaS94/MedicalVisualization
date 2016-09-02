#ifndef VTKVOLUME_H
#define VTKVOLUME_H

#include <QWidget>
#include "window.h"
#include "volume.h"
#include <vtkVolume.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <string>

using namespace std;

class VTKVolume : public Volume
{
private :
    vtkSmartPointer<vtkVolume> volume;
    vtkSmartPointer<vtkDICOMImageReader> data;

public:
    VTKVolume();
    void readData(string foldername);
    void createVolume();
    void render(Window *window );

};

#endif // VTKVOLUME_H
