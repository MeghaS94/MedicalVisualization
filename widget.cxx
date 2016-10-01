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

void Widget::on_checkBox_1_clicked(bool status) {
    controller->setLayer(0, status);
}

void Widget::on_checkBox_2_clicked(bool status) {
    controller->setLayer(1, status);
}

void Widget::on_checkBox_3_clicked(bool status) {
    controller->setLayer(2, status);
}

void Widget::on_checkBox_4_clicked(bool status) {
    controller->setLayer(3, status);
}

void Widget::on_checkBox_5_clicked(bool status) {
    controller->setLayer(4, status);
}

void Widget::on_checkBox_6_clicked(bool status) {
    controller->setLayer(5, status);
}

void Widget::on_checkBox_7_clicked(bool status) {
    controller->setLayer(6, status);
}

void Widget::on_checkBox_8_clicked(bool status) {
    controller->setLayer(7, status);
}

void Widget::on_checkBox_9_clicked(bool status) {
    controller->setLayer(8, status);
}

void Widget::on_checkBox_10_clicked(bool status) {
    controller->setLayer(9, status);
}

void Widget::on_checkBox_11_clicked(bool status) {
    controller->setLayer(10, status);
}

void Widget::on_checkBox_12_clicked(bool status) {
    controller->setLayer(11, status);
}

void Widget::on_checkBox_13_clicked(bool status) {
    controller->setLayer(12, status);
}

void Widget::on_checkBox_14_clicked(bool status) {
    controller->setLayer(13, status);
}

void Widget::on_btnShow_clicked() {
    controller->updateTransferFunctions();
}
