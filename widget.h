#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private slots:
    void on_btnOpen_clicked();

};

#endif // WIDGET_H
