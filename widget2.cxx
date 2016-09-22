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

void Widget2::minIsoValueChanged(int val) {
    controller->setStartIsoValue(val);
    controller->drawSurface();
}

void Widget2::maxIsoValueChanged(int val) {
    controller->setEndIsoValue(val);
    controller->drawSurface();
}
