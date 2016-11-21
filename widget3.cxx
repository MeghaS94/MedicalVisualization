/*
#include "widget3.h"
#include "ui_widget3.h"
#include "controller.h"

Widget3::Widget3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget3)
{
    ui->setupUi(this);
}

Widget3::~Widget3()
{
    delete ui;
}

void Widget3::setController(Controller* c) {
    controller = c;
}
*/

#include "widget3.h"
#include "ui_widget3.h"
#include "controller.h"

Widget3::Widget3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget3)
{
    ui->setupUi(this);
}

Widget3::~Widget3()
{
    delete ui;
}

Ui::Widget3* Widget3::getUi() {
    return ui;
}

void Widget3::setController(Controller* c) {
    controller = c;
}
