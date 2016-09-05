#ifndef SLICE_H
#define SLICE_H

#include <string>
#include "window.h"

using namespace std;

class Slice
{
public:
    Slice(int type);
    void virtual render(Window *window) = 0;
    void virtual readData(string foldername) = 0;
    void virtual createSlice() = 0;
    int getType();

protected:
    int type; //1 for axial, 2 for coronal, 3 for sagittal
};

#endif // SLICE_H
