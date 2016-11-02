#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "window.h"
#include "widget.h"
#include "widget2.h"
#include "imagedata.h"
#include "volume.h"
#include "slice.h"
#include "surface.h"
#include "layer.h"
#include "ui_widget.h"
#include "ui_widget2.h"
#include <string>
#include <vector>

using namespace std;

class Controller
{
public:
    Controller(Ui::Widget* ui_arg1, Ui::Widget2* ui_arg2);
    void setFolderName(string foldername);
    void initialize();
    void initializeVOIButtons();
    void readIsovalues();
    void drawSurface();
    void updateVolumePlanes();
    void setStartIsoValue(int val);
    void setEndIsoValue(int val);
    void extractVOI(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax);
    void axialPlane(bool visibility);
    void coronalPlane(bool visibility);
    void sagittalPlane(bool visibility);
    void setLayer(int i, bool status);
    void updateTransferFunctions();
    void updateSurface(int i);
    void updateThreshold(int val);
    void removeSurfaces();
    void removeSurface();

private:
    Ui::Widget* ui1;
    Ui::Widget2* ui2;
    Window* window1;
    Window* window2;
    Window* window3;
    Window* window4;
    Window* window5;
    ImageData* imageData;
    Volume* volume;
    Slice* axialSlice;
    Slice* coronalSlice;
    Slice* sagittalSlice;
    Surface* surface;
    string foldername;
    vector <Layer> layers;
    bool status;
};

#endif // CONTROLLER_H
