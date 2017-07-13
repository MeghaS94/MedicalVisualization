#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"
#include "vtkimagedata.h"
#include "slice.h"
#include "vtkslice.h"
#include "surface.h"
#include "vtksurface.h"
#include <QInputDialog>
#include <stdlib.h>
#include <string>

using namespace std;

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
    surface = new VTKSurface(0,0,1,1,1);
    status = true;
    currentLayerTab = 0;
}

void Controller::setFolderName(string foldername) {
    this->foldername = foldername;
}


void Controller::initialize()
{
    imageData->loadData(foldername);
    initializeVOIButtons();
    readIsovalues();
    //reads and renders volume
    //volume->readData(foldername);
    volume->setImageData(imageData);
    volume->setLayers(&layers[0], layers.size());
    volume->setCustomLayers(&customLayers[0], customLayers.size());
    volume->createVolume();
    volume->makeIntervals();
    volume->render(window1);

    //axialSlice->readData(foldername);
    axialSlice->setImageDataVolume(imageData, volume);
    axialSlice->createSlice();
    axialSlice->render(window2);

    //coronalSlice->readData(foldername);
    coronalSlice->setImageDataVolume(imageData, volume);
    coronalSlice->createSlice();
    coronalSlice->render(window3);

    //sagittalSlice->readData(foldername);
    sagittalSlice->setImageDataVolume(imageData, volume);
    sagittalSlice->createSlice();
    sagittalSlice->render(window4);

    updateVolumePlanes();

    vector<double> pixel_spacing = imageData->Spacing();
    surface->setSpacing(pixel_spacing);

}

void Controller::makeHistogram()
{
    cout <<" controller : " <<axialSlice->getPointsOnSlice().size() << endl;
    //you can also get intensity range
    cout << "intensity range : " << axialSlice->getIntensityRange()[0] << " , " << axialSlice->getIntensityRange()[1] << endl;
    /*
    QString str = QInputDialog::getText(0, "Enter the slice", " ");
    std::string sliceName = str.toStdString();
    if(sliceName == "coronal")
    {
        coronalSlice->createHistogram();
    }
    else if( sliceName == "sagittal")
    {
        sagittalSlice->createHistogram();
    }
    else if( sliceName == "axial")
    {
        axialSlice->createHistogram();
    }
    */
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

void Controller::readIsovalues() {
    ifstream infile("../isovalues.txt");
    string line;
    char* tokens;
    float isoStart, isoEnd;
    while(getline(infile, line)) {
        tokens = strtok((char *)line.c_str(), ",");
        string name(tokens);
        tokens = strtok(NULL, ",");
        isoStart = atof(tokens);
        tokens = strtok(NULL, ",");
        isoEnd = atof(tokens);
        layers.push_back(Layer(name, isoStart, isoEnd, false));
    }
    customLayers.push_back(Layer("Custom1", 0, 0, false));
    ui1->minBox1->setMinimum((int) imageData->getRange()[0]);
    ui1->minBox1->setMaximum((int) imageData->getRange()[1]);
    ui1->maxBox1->setMinimum((int) imageData->getRange()[0]);
    ui1->maxBox1->setMaximum((int) imageData->getRange()[1]);
    customLayers.push_back(Layer("Custom2", 0, 0, false));
    ui1->minBox2->setMinimum((int) imageData->getRange()[0]);
    ui1->minBox2->setMaximum((int) imageData->getRange()[1]);
    ui1->maxBox2->setMinimum((int) imageData->getRange()[0]);
    ui1->maxBox2->setMaximum((int) imageData->getRange()[1]);
    customLayers.push_back(Layer("Custom3", 0, 0, false));
    ui1->minBox3->setMinimum((int) imageData->getRange()[0]);
    ui1->minBox3->setMaximum((int) imageData->getRange()[1]);
    ui1->maxBox3->setMinimum((int) imageData->getRange()[0]);
    ui1->maxBox3->setMaximum((int) imageData->getRange()[1]);
    customLayers.push_back(Layer("Custom4", 0, 0, false));
    ui1->minBox4->setMinimum((int) imageData->getRange()[0]);
    ui1->minBox4->setMaximum((int) imageData->getRange()[1]);
    ui1->maxBox4->setMinimum((int) imageData->getRange()[0]);
    ui1->maxBox4->setMaximum((int) imageData->getRange()[1]);
    customLayers.push_back(Layer("Custom5", 0, 0, false));
    ui1->minBox5->setMinimum((int) imageData->getRange()[0]);
    ui1->minBox5->setMaximum((int) imageData->getRange()[1]);
    ui1->maxBox5->setMinimum((int) imageData->getRange()[0]);
    ui1->maxBox5->setMaximum((int) imageData->getRange()[1]);
}


void Controller::pickPointsOnsliceMode(bool pickPtsMode)
{
    //whichever slice is chosen, set its pickPtsmode to true
    axialSlice->setSliceMode(pickPtsMode);
}

void Controller::drawSurface() {
    //ui2->min->setText(QString::number(startIsoValue));
    //ui2->max->setText(QString::number(endIsoValue));
    //ui2->horizontalSlider->setMaximum((int) volume->getMaxIntensity());
    //ui2->horizontalSlider_2->setMaximum((int) volume->getMaxIntensity());
    //ui2->horizontalSlider->setMinimum((int) volume->getMinIntensity());
    //ui2->horizontalSlider_2->setMinimum((int) volume->getMinIntensity());
    //surface->readData(foldername);
    //surface->createSurface();
    //surface->render(window5);
 //   cout <<" controller : " <<axialSlice->getPointsOnSlice().size() << endl;
    //you can also get intensity range
   // cout << "intensity range : " << axialSlice->getIntensityRange()[0] << " , " << axialSlice->getIntensityRange()[1] << endl;

    cout << axialSlice->getSliceMode()<< endl;
    if(axialSlice->getSliceMode())
     {

    surface->setIsovalueStart(axialSlice->getIntensityRange()[0]);
    surface->setIsovalueEnd(axialSlice->getIntensityRange()[1]);
    surface->setPtsOnSlice(axialSlice->getPointsOnSlice());
    //cout << "intensity in controller from surface " <<surface->getIsovalueStart() << " , " << surface->getIsovalueEnd() << endl;
    //cout << "number of picked points that surface got :     "<<surface->getPtsOnSlice().size() << endl;
    //surface->copyData();
//    surface->createSurface1();


    ui2->surface->setText("Complete Surface");
    ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
    volume->addPadding();
    surface->setImageData(imageData);
    if(currentLayerTab!=0)
        surface->setLayers(&layers[0], layers.size());
    else
        surface->setLayers(&customLayers[0], customLayers.size());




    surface->createSurface1();
    //surface->createSurface1();
    surface->render(window5);
    ui2->threshold->setMinimum(surface->getMinimum());
    ui2->threshold->setMaximum(surface->getMaximum());
    ui2->threshold->setValue(5000);
    }

    ui2->surface->setText("Complete Surface");
        ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
        volume->addPadding();
        surface->setImageData(imageData);
        if(currentLayerTab!=0)
            surface->setLayers(&layers[0], layers.size());
        else
            surface->setLayers(&customLayers[0], customLayers.size());
        surface->createSurface();
        surface->render(window5);
        ui2->threshold->setMinimum(surface->getMinimum());
        ui2->threshold->setMaximum(surface->getMaximum());
        ui2->threshold->setValue(5000);
}

void Controller::updateSurface(int i) {
    QString Number;
    if(i==0) {
        surface->showCompleteSurface();
        status = true;
        ui2->surface->setText("Complete Surface");
        ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
    }
    else if(i==1) {
        surface->showNextSurface();
        if(!status) {
            surface->showComponentSurface();
            Number.setNum(surface->getCurrentSurface());
            QString s = "Connected Surface "+ Number;
            ui2->surface->setText(s);
            ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
        }
    }
    else if(i==2) {
        surface->showComponentSurface();
        status = false;
        Number.setNum(surface->getCurrentSurface());
        QString s = "Connected Surface "+ Number;
        ui2->surface->setText(s);
        ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
    }
    else {
        surface->showPreviousSurface();
        if(!status) {
            surface->showComponentSurface();
            Number.setNum(surface->getCurrentSurface());
            QString s = "Connected Surface "+ Number;
            ui2->surface->setText(s);
            ui2->number->setText(QString::number(surface->getNumberOfTriangles(status)));
        }
    }
}

void Controller::updateThreshold(int val) {
    surface->updateThreshold(val);
}

void Controller::removeSurfaces() {
    surface->removeSurfaces();
}

void Controller::removeSurface() {
    surface->removeSurface();
}

void Controller::updateVolumePlanes() {
    volume->updatePlane(axialSlice, 1);
    volume->updatePlane(coronalSlice, 2);
    volume->updatePlane(sagittalSlice,3);
    ui1->axial->setText(QString::number(axialSlice->getPosition()));
    ui1->coronal->setText(QString::number(coronalSlice->getPosition()));
    ui1->sagittal->setText(QString::number(sagittalSlice->getPosition()));
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

void Controller::setLayer(int i, bool status) {
    volume->changeLayerMode(1);
    currentLayerTab=1;
    layers[i].on=status;
}

void Controller::setCustomLayer(int i, bool status) {
    volume->changeLayerMode(0);
    currentLayerTab=0;
    customLayers[i].on=status;
}

void Controller::customValMin(int i, int val) {
    customLayers[i].isovalueStart = (float) val;
    //cout << layers[layers.size()-1].isovalueStart << endl;
    volume->updateTransferFunctions();
    axialSlice->updateTransferFunction();
    sagittalSlice->updateTransferFunction();
    coronalSlice->updateTransferFunction();
}

void Controller::customValMax(int i, int val) {
    customLayers[i].isovalueEnd = (float) val;
    //cout << layers[layers.size()-1].isovalueEnd << endl;
    volume->updateTransferFunctions();
    axialSlice->updateTransferFunction();
    sagittalSlice->updateTransferFunction();
    coronalSlice->updateTransferFunction();
}

void Controller::changeLayerMode(int mode) {
    volume->changeLayerMode(mode);
    currentLayerTab=mode;
}

void Controller::updateTransferFunctions() {
    volume->updateTransferFunctions();
    axialSlice->updateTransferFunction();
    sagittalSlice->updateTransferFunction();
    coronalSlice->updateTransferFunction();
}

void Controller::resetTransferFunctions() {
    volume->changeLayerMode(-1);
    volume->updateTransferFunctions();
    axialSlice->updateTransferFunction();
    sagittalSlice->updateTransferFunction();
    coronalSlice->updateTransferFunction();
}

void Controller::changeMode(int mode) {
    surface->changeMode(mode);
}

void Controller::addAnnotation() {
    surface->addAnnotation();
}

void Controller::print() {
    surface->print();
}
