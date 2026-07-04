/********************************************************************************
** Form generated from reading UI file 'bloodpressure_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOODPRESSURE_DIALOG_H
#define UI_BLOODPRESSURE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_BloodPressure_Dialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_name;
    QLabel *lab_age;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLCDNumber *num_HBP;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLCDNumber *num_LBP;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLCDNumber *num_PULSE;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_quit;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_7;
    QwtPlot *Plot_Blood;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_16;

    void setupUi(QDialog *BloodPressure_Dialog)
    {
        if (BloodPressure_Dialog->objectName().isEmpty())
            BloodPressure_Dialog->setObjectName("BloodPressure_Dialog");
        BloodPressure_Dialog->resize(750, 460);
        gridLayout = new QGridLayout(BloodPressure_Dialog);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lab_name = new QLabel(BloodPressure_Dialog);
        lab_name->setObjectName("lab_name");
        lab_name->setStyleSheet(QString::fromUtf8("color: rgb(170, 170, 127);\n"
"font: 14pt \"Microsoft YaHei UI\";"));

        horizontalLayout->addWidget(lab_name);

        lab_age = new QLabel(BloodPressure_Dialog);
        lab_age->setObjectName("lab_age");
        lab_age->setStyleSheet(QString::fromUtf8("color: rgb(170, 170, 127);\n"
"font: 14pt \"Microsoft YaHei UI\";"));

        horizontalLayout->addWidget(lab_age);


        gridLayout->addLayout(horizontalLayout, 0, 14, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 15, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_14, 0, 7, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(BloodPressure_Dialog);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"font: 18pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(label);

        num_HBP = new QLCDNumber(BloodPressure_Dialog);
        num_HBP->setObjectName("num_HBP");
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        num_HBP->setPalette(palette);
        num_HBP->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        verticalLayout->addWidget(num_HBP);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(BloodPressure_Dialog);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);\n"
"font: 18pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(label_2);

        num_LBP = new QLCDNumber(BloodPressure_Dialog);
        num_LBP->setObjectName("num_LBP");
        num_LBP->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        verticalLayout->addWidget(num_LBP);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(BloodPressure_Dialog);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(205, 205, 0);\n"
"font: 18pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(label_3);

        num_PULSE = new QLCDNumber(BloodPressure_Dialog);
        num_PULSE->setObjectName("num_PULSE");
        num_PULSE->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 127);"));

        verticalLayout->addWidget(num_PULSE);


        gridLayout->addLayout(verticalLayout, 2, 15, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_13, 0, 9, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_15, 0, 3, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalSpacer_3 = new QSpacerItem(17, 37, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_2->addItem(verticalSpacer_3);


        gridLayout->addLayout(horizontalLayout_2, 2, 17, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_12, 0, 11, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 13, 1, 1);

        btn_quit = new QPushButton(BloodPressure_Dialog);
        btn_quit->setObjectName("btn_quit");
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource_inside/images/back.png);\n"
"height:25px;\n"
"width:25px\n"
""));

        gridLayout->addWidget(btn_quit, 0, 17, 2, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 4, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");

        gridLayout->addLayout(verticalLayout_2, 3, 15, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 8, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 2, 16, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 10, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 5, 1, 1);

        Plot_Blood = new QwtPlot(BloodPressure_Dialog);
        Plot_Blood->setObjectName("Plot_Blood");

        gridLayout->addWidget(Plot_Blood, 1, 0, 3, 15);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_11, 0, 12, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_16, 0, 2, 1, 1);


        retranslateUi(BloodPressure_Dialog);

        QMetaObject::connectSlotsByName(BloodPressure_Dialog);
    } // setupUi

    void retranslateUi(QDialog *BloodPressure_Dialog)
    {
        BloodPressure_Dialog->setWindowTitle(QCoreApplication::translate("BloodPressure_Dialog", "Dialog", nullptr));
        lab_name->setText(QCoreApplication::translate("BloodPressure_Dialog", "TextLabel", nullptr));
        lab_age->setText(QCoreApplication::translate("BloodPressure_Dialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("BloodPressure_Dialog", "HBP", nullptr));
        label_2->setText(QCoreApplication::translate("BloodPressure_Dialog", "LBP", nullptr));
        label_3->setText(QCoreApplication::translate("BloodPressure_Dialog", "PULSE", nullptr));
        btn_quit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BloodPressure_Dialog: public Ui_BloodPressure_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOODPRESSURE_DIALOG_H
