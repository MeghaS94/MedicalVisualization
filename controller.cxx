#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"
#include "slice.h"
#include "vtkslice.h"
#include "surface.h"
#include "vtksurface.h"

Controller::Controller(Ui::Widget* ui_arg)
{
    ui = ui_arg;
    window1 = new VTKWindow(ui->widget1);
    window2 = new VTKWindow(ui->widget2);
    window3 = new VTKWindow(ui->widget3);
    window4 = new VTKWindow(ui->widget4);
    volume = new VTKVolume();
    axialSlice = new VTKSlice(1, this);
    coronalSlice = new VTKSlice(2, this);
    sagittalSlice = new VTKSlice(3, this);
}

void Controller::loadVolume(string foldername)
{
   //reads and renders volume
   volume->readData(foldername);
   volume->createVolume();
   volume->makeIntervals();
   volume->render(window1);


   /*
   axialSlice->readData(foldername);
   axialSlice->createSlice();
   axialSlice->render(window2);

   coronalSlice->readData(foldername);
   coronalSlice->createSlice();
   coronalSlice->render(window3);

   sagittalSlice->readData(foldername);
   sagittalSlice->createSlice();
   sagittalSlice->render(window4);

   updateVolumePlanes();
*/
   Surface* surface = new VTKSurface(30,60,1,1,1);
   surface->readData(foldername);
   surface->createSurface();
   surface->render(window2);
}

void Controller::updateVolumePlanes() {
    volume->updatePlane(axialSlice, 1);
    volume->updatePlane(coronalSlice, 2);
    volume->updatePlane(sagittalSlice,3);
}

