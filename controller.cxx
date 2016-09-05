#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"
#include "slice.h"
#include "vtkslice.h"

Controller::Controller(Ui::Widget* ui_arg)
{
    ui = ui_arg;
    window1 = new VTKWindow(ui->widget1);
    window2 = new VTKWindow(ui->widget2);
    window3 = new VTKWindow(ui->widget3);
    window4 = new VTKWindow(ui->widget4);
}

void Controller::loadVolume(string foldername)
{
   //reads and renders volume
   Volume* volume = new VTKVolume();
   volume->readData(foldername);
   volume->createVolume();
   volume->render(window1);

   Slice* axialSlice = new VTKSlice(1);
   axialSlice->readData(foldername);
   axialSlice->createSlice();
   axialSlice->render(window2);

   Slice* coronalSlice = new VTKSlice(2);
   coronalSlice->readData(foldername);
   coronalSlice->createSlice();
   coronalSlice->render(window3);

   Slice* sagittalSlice = new VTKSlice(3);
   sagittalSlice->readData(foldername);
   sagittalSlice->createSlice();
   sagittalSlice->render(window4);

}
