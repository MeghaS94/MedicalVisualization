#include "controller.h"
#include "vtkwindow.h"
#include "volume.h"
#include "vtkvolume.h"
#include "vtkimagedata.h"
#include "slice.h"
#include "vtkslice.h"
#include "surface.h"
#include "vtksurface.h"
#include <stdlib.h>
#include <string>

#include <QInputDialog>
#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkPlot.h>
#include <vtkTable.h>
#include <vtkIntArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkRenderWindowInteractor.h>

#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()


using namespace std;

Controller::Controller(Ui::Widget* ui_arg1, Ui::Widget2* ui_arg2, Ui::Widget3* ui_arg3)
{
    ui1 = ui_arg1;
    ui2 = ui_arg2;
    ui3 = ui_arg3;
    window1 = new VTKWindow(ui1->widget1);
    window2 = new VTKWindow(ui1->widget2);
    window3 = new VTKWindow(ui1->widget3);
    window4 = new VTKWindow(ui1->widget4);
    window5 = new VTKWindow(ui2->widget5);
    window6 = new VTKWindow(ui3->widget);
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
/* int type1 = 1;
 double position_axial = axialSlice->getPosition(); //z

 int type2 = 2;
 double position_coronal = coronalSlice->getPosition(); //y

 int type3 = 3;
 double position_sagittal = sagittalSlice->getPosition(); //x
*/


    // write data to stl format
    QString str = QInputDialog::getText(0, "Enter the slice", " ");
    std::string sliceName = str.toStdString();

    vector<double> I;
    if(sliceName == "coronal")
    {
    I = coronalSlice->intensity();
    }
    else if( sliceName == "sagittal")
    {
    I = sagittalSlice->intensity();
    }
    else if( sliceName == "axial")
    {
    I = axialSlice->intensity();
    }

  cout << I.size() << endl;
  //coronalSlice->render(window6);
  set<double> distinct_intensities(I.begin(), I.end());
  cout << distinct_intensities.size() << endl;

  set<double>::iterator it;

  vector<int> data_2008;

  cout << "set" << endl;
  for (it =distinct_intensities.begin(); it!= distinct_intensities.end();it++)
  {
      //cout << *it << endl;
      int value = *it;
      int countI = count(I.begin(), I.end(), value);
      data_2008.push_back(countI);
  }


  VTK_CREATE(vtkContextView, view);
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetSize(400, 300);
    VTK_CREATE(vtkChartXY, chart);
    view->GetScene()->AddItem(chart);

    // Create a table with some points in it...
    VTK_CREATE(vtkTable, table);

    VTK_CREATE(vtkIntArray, arrMonth);
    arrMonth->SetName("Month");
    table->AddColumn(arrMonth);

    VTK_CREATE(vtkIntArray, arr2008);
    arr2008->SetName("2008");
    table->AddColumn(arr2008);
/*
    VTK_CREATE(vtkIntArray, arr2009);
    arr2009->SetName("2009");
    table->AddColumn(arr2009);

    VTK_CREATE(vtkIntArray, arr2010);
    arr2010->SetName("2010");
    table->AddColumn(arr2010);
*/
    table->SetNumberOfRows(distinct_intensities.size());
    for (int i = 0; i < distinct_intensities.size(); i++)
      {
      table->SetValue(i,0,i+1);
      table->SetValue(i,1,data_2008[i]);
      //table->SetValue(i,2,data_2009[i]);
      //table->SetValue(i,3,data_2010[i]);
      }

    // Add multiple line plots, setting the colors etc
    vtkPlot *line = 0;

    line = chart->AddPlot(vtkChart::BAR);
  #if VTK_MAJOR_VERSION <= 5
    line->SetInput(table, 0, 1);
  #else
    line->SetInputData(table, 0, 1);
  #endif
    line->SetColor(0, 255, 0, 255);
/*
    line = chart->AddPlot(vtkChart::BAR);
  #if VTK_MAJOR_VERSION <= 5
    line->SetInput(table, 0, 2);
  #else
    line->SetInputData(table, 0, 2);
  #endif
    line->SetColor(255, 0, 0, 255);

    line = chart->AddPlot(vtkChart::BAR);
  #if VTK_MAJOR_VERSION <= 5
    line->SetInput(table, 0, 3);
  #else
    line->SetInputData(table, 0, 3);
  #endif
    line->SetColor(0, 0, 255, 255);

  */  //Finally render the scene and compare the image to a reference image
    view->GetRenderWindow()->SetMultiSamples(0);
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();

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
