#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>
#include <string>

using namespace std;

class Controller;

namespace Ui {
class Widget2;
}

class Widget2 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget2(QWidget *parent = 0);
    ~Widget2();
    Ui::Widget2* getUi();
    void setController(Controller* c);

private:
    Ui::Widget2 *ui;
    Controller* controller;

private slots:
    void minIsoValueChanged(int val);
    void maxIsoValueChanged(int val);
};

#endif // WIDGET2_H
