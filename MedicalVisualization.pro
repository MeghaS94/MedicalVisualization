#-------------------------------------------------
#
# Project created by QtCreator 2016-09-02T17:06:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MedicalVisualization
TEMPLATE = app

LIBS += -L/usr/local/Cellar/vtk/7.0.0_2/lib #folder to your VTK library

INCLUDEPATH += /usr/local/Cellar/vtk/7.0.0_2/include/vtk-7.0 #folder to your VTK include files

SOURCES +=\
    window.cxx \
    widget.cxx \
    vtkwindow.cxx \
    vtkvolume.cxx \
    vtkslice.cxx \
    volume.cxx \
    slice.cxx \
    main.cxx \
    controller.cxx

HEADERS  += widget.h \
    window.h \
    vtkwindow.h \
    controller.h \
    volume.h \
    vtkvolume.h \
    slice.h \
    vtkslice.h

FORMS    += widget.ui
