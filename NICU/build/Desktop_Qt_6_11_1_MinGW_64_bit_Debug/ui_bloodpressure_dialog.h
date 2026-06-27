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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_BloodPressure_Dialog
{
public:
    QLabel *lab_name;
    QLabel *lab_age;
    QwtPlot *Plot_Blood;
    QLCDNumber *num_HBP;
    QLCDNumber *num_LBP;
    QLCDNumber *num_PULSE;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *btn_quit;

    void setupUi(QDialog *BloodPressure_Dialog)
    {
        if (BloodPressure_Dialog->objectName().isEmpty())
            BloodPressure_Dialog->setObjectName("BloodPressure_Dialog");
        BloodPressure_Dialog->resize(723, 459);
        lab_name = new QLabel(BloodPressure_Dialog);
        lab_name->setObjectName("lab_name");
        lab_name->setGeometry(QRect(510, 10, 54, 16));
        lab_age = new QLabel(BloodPressure_Dialog);
        lab_age->setObjectName("lab_age");
        lab_age->setGeometry(QRect(590, 10, 54, 16));
        Plot_Blood = new QwtPlot(BloodPressure_Dialog);
        Plot_Blood->setObjectName("Plot_Blood");
        Plot_Blood->setGeometry(QRect(-10, 40, 580, 400));
        num_HBP = new QLCDNumber(BloodPressure_Dialog);
        num_HBP->setObjectName("num_HBP");
        num_HBP->setGeometry(QRect(630, 140, 64, 23));
        num_LBP = new QLCDNumber(BloodPressure_Dialog);
        num_LBP->setObjectName("num_LBP");
        num_LBP->setGeometry(QRect(630, 220, 64, 23));
        num_PULSE = new QLCDNumber(BloodPressure_Dialog);
        num_PULSE->setObjectName("num_PULSE");
        num_PULSE->setGeometry(QRect(630, 340, 64, 23));
        label = new QLabel(BloodPressure_Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(630, 80, 54, 16));
        label_2 = new QLabel(BloodPressure_Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(630, 180, 54, 16));
        label_3 = new QLabel(BloodPressure_Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(630, 300, 54, 16));
        btn_quit = new QPushButton(BloodPressure_Dialog);
        btn_quit->setObjectName("btn_quit");
        btn_quit->setGeometry(QRect(700, 0, 25, 25));
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource_inside/images/back.png);"));

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
