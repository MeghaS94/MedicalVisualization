#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "window.h"
#include "widget.h"

class Controller
{
public:
    Controller(Ui::Widget* ui_arg);

private:
    Ui::Widget* ui;
    Window* window1;
    Window* window2;
    Window* window3;
    Window* window4;
};

#endif // CONTROLLER_H
