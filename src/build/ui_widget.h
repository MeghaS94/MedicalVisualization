/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVTKWidget *widget1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QVTKWidget *widget2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QVTKWidget *widget3;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QVTKWidget *widget4;
    QPushButton *btnOpen;
    QPushButton *btnGenerate;
    QGroupBox *groupBox;
    QCheckBox *checkAxial;
    QCheckBox *checkCoronal;
    QCheckBox *checkSagittal;
    QLabel *axial;
    QLabel *coronal;
    QLabel *sagittal;
    QPushButton *extractVOI;
    QGroupBox *groupBox_2;
    QSpinBox *xmin;
    QSpinBox *xmax;
    QSpinBox *ymin;
    QSpinBox *ymax;
    QSpinBox *zmin;
    QSpinBox *zmax;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btnReset;
    QTabWidget *tabMode;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QCheckBox *checkBox_15;
    QSpinBox *minBox1;
    QLabel *label_7;
    QSpinBox *maxBox1;
    QSpinBox *minBox2;
    QLabel *label_8;
    QSpinBox *maxBox2;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_17;
    QSpinBox *minBox3;
    QLabel *label_9;
    QSpinBox *maxBox3;
    QCheckBox *checkBox_18;
    QSpinBox *minBox4;
    QLabel *label_10;
    QSpinBox *maxBox4;
    QCheckBox *checkBox_19;
    QSpinBox *minBox5;
    QLabel *label_11;
    QSpinBox *maxBox5;
    QWidget *tab_2;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QPushButton *btnHistogram;
    QCheckBox *checkBox;
    QCheckBox *checkPickPtsOnSlice;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1307, 935);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 541, 391));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget1 = new QVTKWidget(gridLayoutWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));

        gridLayout->addWidget(widget1, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(Widget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(560, 10, 531, 391));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget2 = new QVTKWidget(gridLayoutWidget_2);
        widget2->setObjectName(QString::fromUtf8("widget2"));

        gridLayout_2->addWidget(widget2, 0, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(Widget);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(9, 409, 541, 391));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget3 = new QVTKWidget(gridLayoutWidget_3);
        widget3->setObjectName(QString::fromUtf8("widget3"));

        gridLayout_3->addWidget(widget3, 0, 0, 1, 1);

        gridLayoutWidget_4 = new QWidget(Widget);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(560, 410, 531, 391));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget4 = new QVTKWidget(gridLayoutWidget_4);
        widget4->setObjectName(QString::fromUtf8("widget4"));

        gridLayout_4->addWidget(widget4, 0, 0, 1, 1);

        btnOpen = new QPushButton(Widget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(1110, 10, 113, 32));
        btnGenerate = new QPushButton(Widget);
        btnGenerate->setObjectName(QString::fromUtf8("btnGenerate"));
        btnGenerate->setGeometry(QRect(1200, 760, 91, 32));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1110, 50, 181, 91));
        checkAxial = new QCheckBox(groupBox);
        checkAxial->setObjectName(QString::fromUtf8("checkAxial"));
        checkAxial->setGeometry(QRect(20, 20, 86, 20));
        checkAxial->setChecked(true);
        checkCoronal = new QCheckBox(groupBox);
        checkCoronal->setObjectName(QString::fromUtf8("checkCoronal"));
        checkCoronal->setGeometry(QRect(20, 40, 86, 20));
        checkCoronal->setChecked(true);
        checkSagittal = new QCheckBox(groupBox);
        checkSagittal->setObjectName(QString::fromUtf8("checkSagittal"));
        checkSagittal->setGeometry(QRect(20, 60, 86, 20));
        checkSagittal->setChecked(true);
        axial = new QLabel(groupBox);
        axial->setObjectName(QString::fromUtf8("axial"));
        axial->setGeometry(QRect(99, 20, 71, 21));
        coronal = new QLabel(groupBox);
        coronal->setObjectName(QString::fromUtf8("coronal"));
        coronal->setGeometry(QRect(100, 40, 71, 21));
        sagittal = new QLabel(groupBox);
        sagittal->setObjectName(QString::fromUtf8("sagittal"));
        sagittal->setGeometry(QRect(100, 60, 71, 21));
        extractVOI = new QPushButton(Widget);
        extractVOI->setObjectName(QString::fromUtf8("extractVOI"));
        extractVOI->setGeometry(QRect(1110, 360, 113, 32));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setGeometry(QRect(1110, 180, 141, 181));
        xmin = new QSpinBox(groupBox_2);
        xmin->setObjectName(QString::fromUtf8("xmin"));
        xmin->setGeometry(QRect(60, 40, 48, 24));
        xmax = new QSpinBox(groupBox_2);
        xmax->setObjectName(QString::fromUtf8("xmax"));
        xmax->setGeometry(QRect(60, 60, 48, 24));
        ymin = new QSpinBox(groupBox_2);
        ymin->setObjectName(QString::fromUtf8("ymin"));
        ymin->setGeometry(QRect(60, 90, 48, 24));
        ymax = new QSpinBox(groupBox_2);
        ymax->setObjectName(QString::fromUtf8("ymax"));
        ymax->setGeometry(QRect(60, 110, 48, 24));
        zmin = new QSpinBox(groupBox_2);
        zmin->setObjectName(QString::fromUtf8("zmin"));
        zmin->setGeometry(QRect(60, 140, 48, 24));
        zmax = new QSpinBox(groupBox_2);
        zmax->setObjectName(QString::fromUtf8("zmax"));
        zmax->setGeometry(QRect(60, 160, 48, 24));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 31, 21));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 31, 21));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 31, 21));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 110, 31, 21));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 140, 31, 21));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 160, 31, 21));
        btnReset = new QPushButton(Widget);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));
        btnReset->setGeometry(QRect(1110, 760, 71, 32));
        tabMode = new QTabWidget(Widget);
        tabMode->setObjectName(QString::fromUtf8("tabMode"));
        tabMode->setGeometry(QRect(1110, 440, 191, 311));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, -10, 191, 291));
        checkBox_15 = new QCheckBox(groupBox_4);
        checkBox_15->setObjectName(QString::fromUtf8("checkBox_15"));
        checkBox_15->setGeometry(QRect(10, 20, 87, 20));
        minBox1 = new QSpinBox(groupBox_4);
        minBox1->setObjectName(QString::fromUtf8("minBox1"));
        minBox1->setGeometry(QRect(20, 40, 71, 24));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(90, 40, 20, 20));
        maxBox1 = new QSpinBox(groupBox_4);
        maxBox1->setObjectName(QString::fromUtf8("maxBox1"));
        maxBox1->setGeometry(QRect(100, 40, 71, 24));
        minBox2 = new QSpinBox(groupBox_4);
        minBox2->setObjectName(QString::fromUtf8("minBox2"));
        minBox2->setGeometry(QRect(20, 90, 71, 24));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(90, 90, 20, 20));
        maxBox2 = new QSpinBox(groupBox_4);
        maxBox2->setObjectName(QString::fromUtf8("maxBox2"));
        maxBox2->setGeometry(QRect(100, 90, 71, 24));
        checkBox_16 = new QCheckBox(groupBox_4);
        checkBox_16->setObjectName(QString::fromUtf8("checkBox_16"));
        checkBox_16->setGeometry(QRect(10, 70, 87, 20));
        checkBox_17 = new QCheckBox(groupBox_4);
        checkBox_17->setObjectName(QString::fromUtf8("checkBox_17"));
        checkBox_17->setGeometry(QRect(10, 120, 87, 20));
        minBox3 = new QSpinBox(groupBox_4);
        minBox3->setObjectName(QString::fromUtf8("minBox3"));
        minBox3->setGeometry(QRect(20, 140, 71, 24));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(90, 140, 20, 20));
        maxBox3 = new QSpinBox(groupBox_4);
        maxBox3->setObjectName(QString::fromUtf8("maxBox3"));
        maxBox3->setGeometry(QRect(100, 140, 71, 24));
        checkBox_18 = new QCheckBox(groupBox_4);
        checkBox_18->setObjectName(QString::fromUtf8("checkBox_18"));
        checkBox_18->setGeometry(QRect(10, 170, 87, 20));
        minBox4 = new QSpinBox(groupBox_4);
        minBox4->setObjectName(QString::fromUtf8("minBox4"));
        minBox4->setGeometry(QRect(20, 190, 71, 24));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(90, 190, 20, 20));
        maxBox4 = new QSpinBox(groupBox_4);
        maxBox4->setObjectName(QString::fromUtf8("maxBox4"));
        maxBox4->setGeometry(QRect(100, 190, 71, 24));
        checkBox_19 = new QCheckBox(groupBox_4);
        checkBox_19->setObjectName(QString::fromUtf8("checkBox_19"));
        checkBox_19->setGeometry(QRect(10, 220, 87, 20));
        minBox5 = new QSpinBox(groupBox_4);
        minBox5->setObjectName(QString::fromUtf8("minBox5"));
        minBox5->setGeometry(QRect(20, 240, 71, 24));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(90, 240, 20, 20));
        maxBox5 = new QSpinBox(groupBox_4);
        maxBox5->setObjectName(QString::fromUtf8("maxBox5"));
        maxBox5->setGeometry(QRect(100, 240, 71, 24));
        tabMode->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, -20, 171, 311));
        groupBox_3->setAutoFillBackground(false);
        checkBox_1 = new QCheckBox(groupBox_3);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(0, 20, 86, 20));
        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(0, 40, 161, 21));
        QFont font;
        font.setPointSize(13);
        checkBox_2->setFont(font);
        checkBox_3 = new QCheckBox(groupBox_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(0, 60, 161, 20));
        checkBox_4 = new QCheckBox(groupBox_3);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(0, 80, 161, 20));
        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(0, 100, 151, 20));
        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(0, 120, 111, 20));
        checkBox_7 = new QCheckBox(groupBox_3);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(0, 140, 121, 20));
        checkBox_8 = new QCheckBox(groupBox_3);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(0, 160, 131, 20));
        checkBox_9 = new QCheckBox(groupBox_3);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(0, 180, 131, 20));
        checkBox_10 = new QCheckBox(groupBox_3);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setGeometry(QRect(0, 200, 151, 20));
        checkBox_11 = new QCheckBox(groupBox_3);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setGeometry(QRect(0, 220, 151, 20));
        checkBox_12 = new QCheckBox(groupBox_3);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setGeometry(QRect(0, 240, 141, 20));
        checkBox_13 = new QCheckBox(groupBox_3);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));
        checkBox_13->setGeometry(QRect(0, 260, 141, 20));
        checkBox_14 = new QCheckBox(groupBox_3);
        checkBox_14->setObjectName(QString::fromUtf8("checkBox_14"));
        checkBox_14->setGeometry(QRect(0, 280, 101, 20));
        tabMode->addTab(tab_2, QString());
        btnHistogram = new QPushButton(Widget);
        btnHistogram->setObjectName(QString::fromUtf8("btnHistogram"));
        btnHistogram->setGeometry(QRect(1120, 140, 113, 32));
        checkBox = new QCheckBox(Widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(1120, 410, 181, 22));
        checkPickPtsOnSlice = new QCheckBox(Widget);
        checkPickPtsOnSlice->setObjectName(QString::fromUtf8("checkPickPtsOnSlice"));
        checkPickPtsOnSlice->setGeometry(QRect(20, 850, 311, 22));

        retranslateUi(Widget);

        tabMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("Widget", "Open", 0, QApplication::UnicodeUTF8));
        btnGenerate->setText(QApplication::translate("Widget", "Generate", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Widget", "Planes", 0, QApplication::UnicodeUTF8));
        checkAxial->setText(QApplication::translate("Widget", "Axial", 0, QApplication::UnicodeUTF8));
        checkCoronal->setText(QApplication::translate("Widget", "Coronal", 0, QApplication::UnicodeUTF8));
        checkSagittal->setText(QApplication::translate("Widget", "Sagittal", 0, QApplication::UnicodeUTF8));
        axial->setText(QString());
        coronal->setText(QString());
        sagittal->setText(QString());
        extractVOI->setText(QApplication::translate("Widget", "Extract VOI", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Widget", "VOI Dimensions", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "xmin", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Widget", "xmax", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "ymin", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "ymax", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "zmin", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "zmax", 0, QApplication::UnicodeUTF8));
        btnReset->setText(QApplication::translate("Widget", "Reset", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        checkBox_15->setText(QApplication::translate("Widget", "Range 1", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Widget", "-", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Widget", "-", 0, QApplication::UnicodeUTF8));
        checkBox_16->setText(QApplication::translate("Widget", "Range 2", 0, QApplication::UnicodeUTF8));
        checkBox_17->setText(QApplication::translate("Widget", "Range 3", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Widget", "-", 0, QApplication::UnicodeUTF8));
        checkBox_18->setText(QApplication::translate("Widget", "Range 4", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Widget", "-", 0, QApplication::UnicodeUTF8));
        checkBox_19->setText(QApplication::translate("Widget", "Range 5", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Widget", "-", 0, QApplication::UnicodeUTF8));
        tabMode->setTabText(tabMode->indexOf(tab), QApplication::translate("Widget", "Custom", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        checkBox_1->setText(QApplication::translate("Widget", "Bone", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("Widget", "Compact Bone (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("Widget", "Compact Bone (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("Widget", "Spongial Bone (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("Widget", "Spongial Bone (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("Widget", "Enamel (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("Widget", "Enamel (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("Widget", "Fat Tissue (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("Widget", "Fat Tissue (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("Widget", "Muscle Tissue (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_11->setText(QApplication::translate("Widget", "Muscle Tissue (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_12->setText(QApplication::translate("Widget", "Skin Tissue (Adult)", 0, QApplication::UnicodeUTF8));
        checkBox_13->setText(QApplication::translate("Widget", "Skin Tissue (Child)", 0, QApplication::UnicodeUTF8));
        checkBox_14->setText(QApplication::translate("Widget", "Soft Tissue", 0, QApplication::UnicodeUTF8));
        tabMode->setTabText(tabMode->indexOf(tab_2), QApplication::translate("Widget", "Default", 0, QApplication::UnicodeUTF8));
        btnHistogram->setText(QApplication::translate("Widget", "Histogram", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Widget", "Use Hounsfield Scale", 0, QApplication::UnicodeUTF8));
        checkPickPtsOnSlice->setText(QApplication::translate("Widget", "Pick points on slice to generate volume", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
