/********************************************************************************
** Form generated from reading UI file 'widget2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET2_H
#define UI_WIDGET2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget2
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVTKWidget *widget5;
    QGroupBox *groupBox;
    QRadioButton *radioBtnComplete;
    QRadioButton *radioBtnComponent;
    QTabWidget *tabMode;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QSpinBox *threshold;
    QPushButton *btnRemove;
    QGroupBox *groupBox_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnPrevious;
    QPushButton *btnNext;
    QLabel *number;
    QLabel *surface;
    QPushButton *btnRemove2;
    QWidget *tab_2;
    QPushButton *btnAnnotation;
    QPushButton *btnPrint;

    void setupUi(QWidget *Widget2)
    {
        if (Widget2->objectName().isEmpty())
            Widget2->setObjectName(QString::fromUtf8("Widget2"));
        Widget2->resize(1201, 810);
        Widget2->setAutoFillBackground(true);
        verticalLayoutWidget = new QWidget(Widget2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 841, 771));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget5 = new QVTKWidget(verticalLayoutWidget);
        widget5->setObjectName(QString::fromUtf8("widget5"));

        verticalLayout->addWidget(widget5);

        groupBox = new QGroupBox(Widget2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(940, 30, 211, 80));
        radioBtnComplete = new QRadioButton(groupBox);
        radioBtnComplete->setObjectName(QString::fromUtf8("radioBtnComplete"));
        radioBtnComplete->setGeometry(QRect(10, 20, 171, 31));
        radioBtnComplete->setChecked(true);
        radioBtnComponent = new QRadioButton(groupBox);
        radioBtnComponent->setObjectName(QString::fromUtf8("radioBtnComponent"));
        radioBtnComponent->setGeometry(QRect(10, 50, 191, 20));
        tabMode = new QTabWidget(Widget2);
        tabMode->setObjectName(QString::fromUtf8("tabMode"));
        tabMode->setGeometry(QRect(900, 160, 271, 341));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 241, 131));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 30, 131, 51));
        label_3->setWordWrap(true);
        threshold = new QSpinBox(groupBox_3);
        threshold->setObjectName(QString::fromUtf8("threshold"));
        threshold->setGeometry(QRect(160, 40, 71, 24));
        threshold->setMaximum(10000);
        threshold->setValue(5000);
        btnRemove = new QPushButton(groupBox_3);
        btnRemove->setObjectName(QString::fromUtf8("btnRemove"));
        btnRemove->setGeometry(QRect(60, 90, 113, 32));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 150, 241, 151));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 60, 16));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 151, 21));
        btnPrevious = new QPushButton(groupBox_2);
        btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
        btnPrevious->setGeometry(QRect(10, 80, 113, 32));
        btnNext = new QPushButton(groupBox_2);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setGeometry(QRect(120, 80, 113, 32));
        number = new QLabel(groupBox_2);
        number->setObjectName(QString::fromUtf8("number"));
        number->setGeometry(QRect(170, 50, 71, 20));
        surface = new QLabel(groupBox_2);
        surface->setObjectName(QString::fromUtf8("surface"));
        surface->setGeometry(QRect(80, 26, 151, 20));
        btnRemove2 = new QPushButton(groupBox_2);
        btnRemove2->setObjectName(QString::fromUtf8("btnRemove2"));
        btnRemove2->setGeometry(QRect(72, 110, 101, 32));
        tabMode->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        btnAnnotation = new QPushButton(tab_2);
        btnAnnotation->setObjectName(QString::fromUtf8("btnAnnotation"));
        btnAnnotation->setGeometry(QRect(60, 40, 151, 32));
        btnPrint = new QPushButton(tab_2);
        btnPrint->setObjectName(QString::fromUtf8("btnPrint"));
        btnPrint->setGeometry(QRect(80, 90, 113, 32));
        tabMode->addTab(tab_2, QString());

        retranslateUi(Widget2);

        tabMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget2);
    } // setupUi

    void retranslateUi(QWidget *Widget2)
    {
        Widget2->setWindowTitle(QApplication::translate("Widget2", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Widget2", "Display", 0, QApplication::UnicodeUTF8));
        radioBtnComplete->setText(QApplication::translate("Widget2", "Complete Surface", 0, QApplication::UnicodeUTF8));
        radioBtnComponent->setText(QApplication::translate("Widget2", "Connected Component", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("Widget2", "Complete Surface", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget2", "Threshold for small component removal (red in colour)", 0, QApplication::UnicodeUTF8));
        btnRemove->setText(QApplication::translate("Widget2", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Widget2", "Connected Component", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget2", "Surface:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget2", "Number of Triangles:", 0, QApplication::UnicodeUTF8));
        btnPrevious->setText(QApplication::translate("Widget2", "Previous", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("Widget2", "Next", 0, QApplication::UnicodeUTF8));
        number->setText(QString());
        surface->setText(QString());
        btnRemove2->setText(QApplication::translate("Widget2", "Remove", 0, QApplication::UnicodeUTF8));
        tabMode->setTabText(tabMode->indexOf(tab), QApplication::translate("Widget2", "Edit", 0, QApplication::UnicodeUTF8));
        btnAnnotation->setText(QApplication::translate("Widget2", "Add Annotation", 0, QApplication::UnicodeUTF8));
        btnPrint->setText(QApplication::translate("Widget2", "Print", 0, QApplication::UnicodeUTF8));
        tabMode->setTabText(tabMode->indexOf(tab_2), QApplication::translate("Widget2", "Pick", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget2: public Ui_Widget2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET2_H
