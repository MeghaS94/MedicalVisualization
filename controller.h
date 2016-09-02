#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "window.h"
#include "widget.h"
#include "ui_widget.h"
#include <string>
/*
namespace Ui {
class Widget;
}*/

using namespace std;

class Controller
{
public:
    Controller(Ui::Widget* ui_arg);
    void loadVolume(string foldername);

private:
    Ui::Widget* ui;
    Window* window1;
    Window* window2;
    Window* window3;
    Window* window4;
};

#endif // CONTROLLER_H
