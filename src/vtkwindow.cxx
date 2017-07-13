#include "vtkwindow.h"

VTKWindow::VTKWindow(QVTKWidget* widget_arg)
{
    widget = widget_arg;
}

QVTKWidget* VTKWindow::getWidget()
{
    return widget;
}
