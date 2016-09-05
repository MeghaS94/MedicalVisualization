#ifndef VTKSLICE_H
#define VTKSLICE_H

#include <vtkImageReslice.h>
#include <vtkImageReader2.h>

#include "slice.h"

class VTKSlice : public Slice
{
private :
    vtkSmartPointer<vtkImageReslice> slice;
    vtkSmartPointer<vtkImageReader2> data;

public:
    VTKSlice(int type);
    void readData(string foldername);
    void createSlice();
    void render(Window *window );
};

#endif // VTKSLICE_H
