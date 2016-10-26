#include "widget2.h"
#include "ui_widget2.h"
#include "controller.h"

Widget2::Widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2)
{
    ui->setupUi(this);
}

Widget2::~Widget2()
{
    delete ui;
}

Ui::Widget2* Widget2::getUi() {
    return ui;
}

void Widget2::setController(Controller* c) {
    controller = c;
}

void Widget2::on_btnPrevious_clicked() {
    controller->updateSurface(-1);
}

void Widget2::on_btnNext_clicked() {
    controller->updateSurface(1);
}

void Widget2::on_radioBtnComplete_clicked() {
    controller->updateSurface(0);
}

void Widget2::on_radioBtnComponent_clicked() {
    controller->updateSurface(2);
}

void Widget2::on_threshold_valueChanged(int val) {
    controller->updateThreshold(val);
}
