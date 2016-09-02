#ifndef VTKWINDOW_H
#define VTKWINDOW_H

#include "window.h"

#include <QVTKWidget.h>

class VTKWindow : public Window
{
public:
    VTKWindow(QVTKWidget* widget_arg);
    QVTKWidget* getWidget();

private:
    QVTKWidget* widget;
};

#endif // VTKWINDOW_H
