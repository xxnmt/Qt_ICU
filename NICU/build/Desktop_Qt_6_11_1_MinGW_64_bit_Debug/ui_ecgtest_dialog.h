/********************************************************************************
** Form generated from reading UI file 'ecgtest_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECGTEST_DIALOG_H
#define UI_ECGTEST_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ECGTest_Dialog
{
public:
    QPushButton *btn_quit;
    QLabel *label_UserName;
    QLabel *label_UserAge;

    void setupUi(QDialog *ECGTest_Dialog)
    {
        if (ECGTest_Dialog->objectName().isEmpty())
            ECGTest_Dialog->setObjectName("ECGTest_Dialog");
        ECGTest_Dialog->resize(669, 449);
        ECGTest_Dialog->setStyleSheet(QString::fromUtf8(""));
        btn_quit = new QPushButton(ECGTest_Dialog);
        btn_quit->setObjectName("btn_quit");
        btn_quit->setGeometry(QRect(630, 10, 25, 25));
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/back.png);"));
        label_UserName = new QLabel(ECGTest_Dialog);
        label_UserName->setObjectName("label_UserName");
        label_UserName->setGeometry(QRect(320, 10, 70, 25));
        QFont font;
        font.setPointSize(12);
        label_UserName->setFont(font);
        label_UserAge = new QLabel(ECGTest_Dialog);
        label_UserAge->setObjectName("label_UserAge");
        label_UserAge->setGeometry(QRect(410, 10, 70, 25));
        label_UserAge->setFont(font);

        retranslateUi(ECGTest_Dialog);

        QMetaObject::connectSlotsByName(ECGTest_Dialog);
    } // setupUi

    void retranslateUi(QDialog *ECGTest_Dialog)
    {
        ECGTest_Dialog->setWindowTitle(QCoreApplication::translate("ECGTest_Dialog", "Dialog", nullptr));
        btn_quit->setText(QString());
        label_UserName->setText(QCoreApplication::translate("ECGTest_Dialog", "TextLabel", nullptr));
        label_UserAge->setText(QCoreApplication::translate("ECGTest_Dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ECGTest_Dialog: public Ui_ECGTest_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECGTEST_DIALOG_H
