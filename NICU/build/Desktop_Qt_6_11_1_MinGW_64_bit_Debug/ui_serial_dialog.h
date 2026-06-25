/********************************************************************************
** Form generated from reading UI file 'serial_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_DIALOG_H
#define UI_SERIAL_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Serial_Dialog
{
public:
    QPushButton *hurryBtn;
    QPushButton *breathTestBtn;
    QPushButton *heartTestBtn;
    QPushButton *bloodPressureBtn;
    QPushButton *serialControl;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QDialog *Serial_Dialog)
    {
        if (Serial_Dialog->objectName().isEmpty())
            Serial_Dialog->setObjectName("Serial_Dialog");
        Serial_Dialog->resize(670, 462);
        hurryBtn = new QPushButton(Serial_Dialog);
        hurryBtn->setObjectName("hurryBtn");
        hurryBtn->setGeometry(QRect(70, 100, 80, 18));
        breathTestBtn = new QPushButton(Serial_Dialog);
        breathTestBtn->setObjectName("breathTestBtn");
        breathTestBtn->setGeometry(QRect(80, 290, 80, 18));
        heartTestBtn = new QPushButton(Serial_Dialog);
        heartTestBtn->setObjectName("heartTestBtn");
        heartTestBtn->setGeometry(QRect(410, 100, 80, 18));
        bloodPressureBtn = new QPushButton(Serial_Dialog);
        bloodPressureBtn->setObjectName("bloodPressureBtn");
        bloodPressureBtn->setGeometry(QRect(420, 280, 80, 18));
        serialControl = new QPushButton(Serial_Dialog);
        serialControl->setObjectName("serialControl");
        serialControl->setGeometry(QRect(250, 380, 80, 18));
        label = new QLabel(Serial_Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 340, 40, 12));
        comboBox = new QComboBox(Serial_Dialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(250, 200, 62, 22));

        retranslateUi(Serial_Dialog);

        QMetaObject::connectSlotsByName(Serial_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Serial_Dialog)
    {
        Serial_Dialog->setWindowTitle(QCoreApplication::translate("Serial_Dialog", "Dialog", nullptr));
        hurryBtn->setText(QCoreApplication::translate("Serial_Dialog", "PushButton", nullptr));
        breathTestBtn->setText(QCoreApplication::translate("Serial_Dialog", "PushButton", nullptr));
        heartTestBtn->setText(QCoreApplication::translate("Serial_Dialog", "PushButton", nullptr));
        bloodPressureBtn->setText(QCoreApplication::translate("Serial_Dialog", "PushButton", nullptr));
        serialControl->setText(QCoreApplication::translate("Serial_Dialog", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("Serial_Dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Serial_Dialog: public Ui_Serial_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_DIALOG_H
