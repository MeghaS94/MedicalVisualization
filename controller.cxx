#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"

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

}
