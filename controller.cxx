#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"
#include "vtkimagedata.h"
#include "slice.h"
#include "vtkslice.h"
#include "surface.h"
#include "vtksurface.h"

Controller::Controller(Ui::Widget* ui_arg1, Ui::Widget2* ui_arg2)
{
    ui1 = ui_arg1;
    ui2 = ui_arg2;
    window1 = new VTKWindow(ui1->widget1);
    window2 = new VTKWindow(ui1->widget2);
    window3 = new VTKWindow(ui1->widget3);
    window4 = new VTKWindow(ui1->widget4);
    window5 = new VTKWindow(ui2->widget5);
    imageData = new VTKImageData();
    volume = new VTKVolume();
    axialSlice = new VTKSlice(1, this);
    coronalSlice = new VTKSlice(2, this);
    sagittalSlice = new VTKSlice(3, this);
    startIsoValue = 0;
    endIsoValue = 100;
    surface = new VTKSurface(startIsoValue,endIsoValue,1,1,1);
}

void Controller::setFolderName(string foldername) {
    this->foldername = foldername;
}

void Controller::initialize()
{
    imageData->loadData(foldername);
    initializeVOIButtons();
    //reads and renders volume
    //volume->readData(foldername);
    volume->setImageData(imageData);
    volume->createVolume();
    volume->makeIntervals();
    volume->render(window1);

    //axialSlice->readData(foldername);
    axialSlice->setImageData(imageData);
    axialSlice->createSlice();
    //axialSlice->render(window2);

    //coronalSlice->readData(foldername);
    coronalSlice->setImageData(imageData);
    coronalSlice->createSlice();
    //coronalSlice->render(window3);

    //sagittalSlice->readData(foldername);
    sagittalSlice->setImageData(imageData);
    sagittalSlice->createSlice();
    //sagittalSlice->render(window4);

    updateVolumePlanes();

}

void Controller::initializeVOIButtons() {
    ui1->xmin->setMinimum(imageData->getExtent()[0]);
    ui1->xmin->setMaximum(imageData->getExtent()[1]);
    ui1->xmin->setValue(imageData->getExtent()[0]);
    ui1->xmax->setMinimum(imageData->getExtent()[0]);
    ui1->xmax->setMaximum(imageData->getExtent()[1]);
    ui1->xmax->setValue(imageData->getExtent()[1]);
    ui1->ymin->setMinimum(imageData->getExtent()[2]);
    ui1->ymin->setMaximum(imageData->getExtent()[3]);
    ui1->ymin->setValue(imageData->getExtent()[2]);
    ui1->ymax->setMinimum(imageData->getExtent()[2]);
    ui1->ymax->setMaximum(imageData->getExtent()[3]);
    ui1->ymax->setValue(imageData->getExtent()[3]);
    ui1->zmin->setMinimum(imageData->getExtent()[4]);
    ui1->zmin->setMaximum(imageData->getExtent()[5]);
    ui1->zmin->setValue(imageData->getExtent()[4]);
    ui1->zmax->setMinimum(imageData->getExtent()[4]);
    ui1->zmax->setMaximum(imageData->getExtent()[5]);
    ui1->zmax->setValue(imageData->getExtent()[5]);
}

void Controller::drawSurface() {
    ui2->min->setText(QString::number(startIsoValue));
    ui2->max->setText(QString::number(endIsoValue));
    ui2->horizontalSlider->setMaximum((int) volume->getMaxIntensity());
    ui2->horizontalSlider_2->setMaximum((int) volume->getMaxIntensity());
    ui2->horizontalSlider->setMinimum((int) volume->getMinIntensity());
    ui2->horizontalSlider_2->setMinimum((int) volume->getMinIntensity());
    //surface->readData(foldername);
    //surface->createSurface();
    //surface->render(window5);
    surface->setImageData(imageData);
    surface->createSurface();
    surface->render(window5);
}

void Controller::updateVolumePlanes() {
    volume->updatePlane(axialSlice, 1);
    volume->updatePlane(coronalSlice, 2);
    volume->updatePlane(sagittalSlice,3);
}

void Controller::setStartIsoValue(int val) {
    startIsoValue = val;
    ui2->min->setText(QString::number(startIsoValue));
    printf("%d %d\n", startIsoValue, endIsoValue);
    surface->setIsovalueStart(startIsoValue);
    QCoreApplication::processEvents();
    surface->createSurface();
}

void Controller::setEndIsoValue(int val) {
    endIsoValue = val;
    ui2->max->setText(QString::number(endIsoValue));
    printf("%d %d\n", startIsoValue, endIsoValue);
    surface->setIsovalueEnd(endIsoValue);
    QCoreApplication::processEvents();
    surface->createSurface();
}

void Controller::extractVOI(int xmin, int xmax, int ymin, int ymax, int zmin, int zmax) {
    if(xmax>=xmin && ymax>=ymin && zmax>=zmin) {
        volume->updateVOI(xmin,xmax,ymin,ymax,zmin,zmax);
        axialSlice->updateSlice();
        coronalSlice->updateSlice();
        sagittalSlice->updateSlice();
        updateVolumePlanes();
    }
}

void Controller::axialPlane(bool visibility) {
    volume->axialPlane(visibility);
}

void Controller::coronalPlane(bool visibility) {
    volume->coronalPlane(visibility);
}

void Controller::sagittalPlane(bool visibility) {
    volume->sagittalPlane(visibility);
}
