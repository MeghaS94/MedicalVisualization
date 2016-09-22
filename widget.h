#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>
#include "widget2.h"

using namespace std;

class Controller;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget* ui;
    Controller* controller;
    Widget2 w;

private slots:
    void on_btnOpen_clicked();
    void on_btnGenerate_clicked();
    void on_extractVOI_clicked();
    void on_checkAxial_clicked(bool status);
    void on_checkCoronal_clicked(bool status);
    void on_checkSagittal_clicked(bool status);
};

#endif // WIDGET_H
