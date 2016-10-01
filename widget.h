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
    void on_checkBox_1_clicked(bool status);
    void on_checkBox_2_clicked(bool status);
    void on_checkBox_3_clicked(bool status);
    void on_checkBox_4_clicked(bool status);
    void on_checkBox_5_clicked(bool status);
    void on_checkBox_6_clicked(bool status);
    void on_checkBox_7_clicked(bool status);
    void on_checkBox_8_clicked(bool status);
    void on_checkBox_9_clicked(bool status);
    void on_checkBox_10_clicked(bool status);
    void on_checkBox_11_clicked(bool status);
    void on_checkBox_12_clicked(bool status);
    void on_checkBox_13_clicked(bool status);
    void on_checkBox_14_clicked(bool status);
    void on_btnShow_clicked();
};

#endif // WIDGET_H
