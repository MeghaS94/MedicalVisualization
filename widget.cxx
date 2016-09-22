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

