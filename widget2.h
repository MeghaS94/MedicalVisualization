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
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_radioBtnComplete_clicked();
    void on_radioBtnComponent_clicked();
    void on_threshold_valueChanged(int val);
    void on_btnRemove_clicked();
    void on_btnRemove2_clicked();
    void on_tabMode_currentChanged(int mode);
    void on_btnAnnotation_clicked();
    void on_btnPrint_clicked();
};

#endif // WIDGET2_H
