/*
#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>
#include <string>

using namespace std;
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
*/

#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>
#include <string>

using namespace std;

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

private slots:
    /*void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_radioBtnComplete_clicked();
    void on_radioBtnComponent_clicked();
    void on_threshold_valueChanged(int val);
    void on_btnRemove_clicked();
    void on_btnRemove2_clicked();
    void on_tabMode_currentChanged(int mode);
    void on_btnAnnotation_clicked();
    void on_btnPrint_clicked();
*/
};

#endif // WIDGET2_H
