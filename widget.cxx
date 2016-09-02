#include "widget.h"
#include "ui_widget.h"

#include <string>
#include <QFileDialog>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    controller = new Controller(ui);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnOpen_clicked() {
    QString folderName = QFileDialog::getExistingDirectory(this,tr("Open Directory"),QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    string stdstrFolderName = folderName.toUtf8().constData();
}
