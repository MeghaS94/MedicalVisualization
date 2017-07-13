#include "widget.h"
#include "ui_widget.h"
#include "widget2.h"
#include <string>
#include <QFileDialog>
#include "controller.h"

using namespace std;

//Controller* Widget::controller = new Controller();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    controller = new Controller(ui, w.getUi());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnOpen_clicked() {
    QString folderName = QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    string stdstrFolderName = folderName.toUtf8().constData();
    controller->setFolderName(stdstrFolderName);
    controller->initialize();
}

void Widget::on_btnGenerate_clicked() {
    w.setController(controller);
    w.show();
    controller->drawSurface();
}

void Widget::on_btnHistogram_clicked()
{
    controller->makeHistogram();
}

void Widget::on_extractVOI_clicked() {
    controller->extractVOI(ui->xmin->value(), ui->xmax->value(), ui->ymin->value(), ui->ymax->value(), ui->zmin->value(), ui->zmax->value());
}

void Widget::on_checkAxial_clicked(bool status) {
    controller->axialPlane(status);
}

void Widget::on_checkCoronal_clicked(bool status) {
    controller->coronalPlane(status);
}

void Widget::on_checkSagittal_clicked(bool status) {
    controller->sagittalPlane(status);
}

void Widget::on_checkPickPtsOnSlice_clicked(bool status)
{
    controller->pickPointsOnsliceMode(status);
}


void Widget::on_checkBox_1_clicked(bool status) {
    controller->setLayer(0, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_2_clicked(bool status) {
    controller->setLayer(1, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_3_clicked(bool status) {
    controller->setLayer(2, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_4_clicked(bool status) {
    controller->setLayer(3, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_5_clicked(bool status) {
    controller->setLayer(4, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_6_clicked(bool status) {
    controller->setLayer(5, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_7_clicked(bool status) {
    controller->setLayer(6, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_8_clicked(bool status) {
    controller->setLayer(7, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_9_clicked(bool status) {
    controller->setLayer(8, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_10_clicked(bool status) {
    controller->setLayer(9, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_11_clicked(bool status) {
    controller->setLayer(10, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_12_clicked(bool status) {
    controller->setLayer(11, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_13_clicked(bool status) {
    controller->setLayer(12, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_14_clicked(bool status) {
    controller->setLayer(13, status);
    controller->updateTransferFunctions();
}

void Widget::on_checkBox_15_clicked(bool status) {
    controller->setCustomLayer(0, status);
    controller->updateTransferFunctions();
}

void Widget::on_minBox1_valueChanged(int val) {
    controller->customValMin(0, val);
}

void Widget::on_maxBox1_valueChanged(int val) {
    controller->customValMax(0, val);
}

void Widget::on_checkBox_16_clicked(bool status) {
    controller->setCustomLayer(1, status);
    controller->updateTransferFunctions();
}

void Widget::on_minBox2_valueChanged(int val) {
    controller->customValMin(1, val);
}

void Widget::on_maxBox2_valueChanged(int val) {
    controller->customValMax(1, val);
}

void Widget::on_checkBox_17_clicked(bool status) {
    controller->setCustomLayer(2, status);
    controller->updateTransferFunctions();
}

void Widget::on_minBox3_valueChanged(int val) {
    controller->customValMin(2, val);
}

void Widget::on_maxBox3_valueChanged(int val) {
    controller->customValMax(2, val);
}

void Widget::on_checkBox_18_clicked(bool status) {
    controller->setCustomLayer(3, status);
    controller->updateTransferFunctions();
}

void Widget::on_minBox4_valueChanged(int val) {
    controller->customValMin(3, val);
}

void Widget::on_maxBox4_valueChanged(int val) {
    controller->customValMax(3, val);
}

void Widget::on_checkBox_19_clicked(bool status) {
    controller->setCustomLayer(4, status);
    controller->updateTransferFunctions();
}

void Widget::on_minBox5_valueChanged(int val) {
    controller->customValMin(4, val);
}

void Widget::on_maxBox5_valueChanged(int val) {
    controller->customValMax(4, val);
}

void Widget::on_tabMode_currentChanged(int mode) {
    //printf("Tab Changeed %d\n", mode);
    controller->changeLayerMode(mode);
    controller->updateTransferFunctions();
}

void Widget::on_btnReset_clicked() {
    controller->resetTransferFunctions();
}
