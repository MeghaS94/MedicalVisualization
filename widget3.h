#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>

class Controller;

namespace Ui {
class Widget3;
}

class Widget3 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget3(QWidget *parent = 0);
    ~Widget3();
    Ui::Widget3* getUi();
    void setController(Controller* c);

private:
    Ui::Widget3 *ui;
    Controller* controller;
};

#endif // WIDGET3_H
