#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "window.h"
#include "widget.h"
#include "volume.h"
#include "slice.h"
#include "ui_widget.h"
#include <string>

using namespace std;

class Controller
{
public:
    Controller(Ui::Widget* ui_arg);
    void loadVolume(string foldername);
    void updateVolumePlanes();

private:
    Ui::Widget* ui;
    Window* window1;
    Window* window2;
    Window* window3;
    Window* window4;
    Volume* volume;
    Slice* axialSlice;
    Slice* coronalSlice;
    Slice* sagittalSlice;
};

#endif // CONTROLLER_H
