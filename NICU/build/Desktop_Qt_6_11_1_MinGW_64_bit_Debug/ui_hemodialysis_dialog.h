/********************************************************************************
** Form generated from reading UI file 'hemodialysis_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEMODIALYSIS_DIALOG_H
#define UI_HEMODIALYSIS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hemodialysis_Dialog
{
public:
    QPushButton *btn_check;
    QPushButton *btn_claen;
    QPushButton *btn_connectD;
    QPushButton *btn_connectJ;
    QPushButton *btn_open;
    QPushButton *btn_fill;
    QPushButton *btn_start;
    QPushButton *btn_emergency;
    QPushButton *btn_quit;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QProgressBar *progressBar_clean;
    QProgressBar *progressBar_D;
    QProgressBar *progressBar_J;
    QProgressBar *progressBar_blood;
    QProgressBar *progressBar_check;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *lab_e;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *namelabel;
    QLabel *agelabel;

    void setupUi(QDialog *Hemodialysis_Dialog)
    {
        if (Hemodialysis_Dialog->objectName().isEmpty())
            Hemodialysis_Dialog->setObjectName("Hemodialysis_Dialog");
        Hemodialysis_Dialog->resize(602, 388);
        btn_check = new QPushButton(Hemodialysis_Dialog);
        btn_check->setObjectName("btn_check");
        btn_check->setGeometry(QRect(40, 30, 80, 18));
        btn_claen = new QPushButton(Hemodialysis_Dialog);
        btn_claen->setObjectName("btn_claen");
        btn_claen->setGeometry(QRect(40, 170, 80, 18));
        btn_connectD = new QPushButton(Hemodialysis_Dialog);
        btn_connectD->setObjectName("btn_connectD");
        btn_connectD->setGeometry(QRect(180, 170, 80, 18));
        btn_connectJ = new QPushButton(Hemodialysis_Dialog);
        btn_connectJ->setObjectName("btn_connectJ");
        btn_connectJ->setGeometry(QRect(310, 170, 80, 18));
        btn_open = new QPushButton(Hemodialysis_Dialog);
        btn_open->setObjectName("btn_open");
        btn_open->setGeometry(QRect(450, 170, 80, 18));
        btn_fill = new QPushButton(Hemodialysis_Dialog);
        btn_fill->setObjectName("btn_fill");
        btn_fill->setGeometry(QRect(80, 340, 80, 18));
        btn_start = new QPushButton(Hemodialysis_Dialog);
        btn_start->setObjectName("btn_start");
        btn_start->setGeometry(QRect(220, 340, 80, 18));
        btn_emergency = new QPushButton(Hemodialysis_Dialog);
        btn_emergency->setObjectName("btn_emergency");
        btn_emergency->setGeometry(QRect(390, 340, 80, 18));
        btn_quit = new QPushButton(Hemodialysis_Dialog);
        btn_quit->setObjectName("btn_quit");
        btn_quit->setGeometry(QRect(570, 0, 25, 25));
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/back.png);"));
        comboBox = new QComboBox(Hemodialysis_Dialog);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(120, 90, 62, 22));
        comboBox_2 = new QComboBox(Hemodialysis_Dialog);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(120, 130, 62, 22));
        progressBar_clean = new QProgressBar(Hemodialysis_Dialog);
        progressBar_clean->setObjectName("progressBar_clean");
        progressBar_clean->setGeometry(QRect(30, 200, 118, 23));
        progressBar_clean->setValue(24);
        progressBar_D = new QProgressBar(Hemodialysis_Dialog);
        progressBar_D->setObjectName("progressBar_D");
        progressBar_D->setGeometry(QRect(160, 200, 118, 23));
        progressBar_D->setValue(24);
        progressBar_J = new QProgressBar(Hemodialysis_Dialog);
        progressBar_J->setObjectName("progressBar_J");
        progressBar_J->setGeometry(QRect(290, 200, 118, 23));
        progressBar_J->setValue(24);
        progressBar_blood = new QProgressBar(Hemodialysis_Dialog);
        progressBar_blood->setObjectName("progressBar_blood");
        progressBar_blood->setGeometry(QRect(430, 200, 118, 23));
        progressBar_blood->setValue(24);
        progressBar_check = new QProgressBar(Hemodialysis_Dialog);
        progressBar_check->setObjectName("progressBar_check");
        progressBar_check->setGeometry(QRect(160, 30, 118, 23));
        progressBar_check->setValue(24);
        gridLayoutWidget = new QWidget(Hemodialysis_Dialog);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(60, 230, 261, 101));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(Hemodialysis_Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 90, 40, 12));
        label_4 = new QLabel(Hemodialysis_Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 130, 71, 16));
        lab_e = new QLabel(Hemodialysis_Dialog);
        lab_e->setObjectName("lab_e");
        lab_e->setGeometry(QRect(379, 231, 101, 81));
        lab_e->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(Hemodialysis_Dialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(340, 0, 86, 14));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        namelabel = new QLabel(widget);
        namelabel->setObjectName("namelabel");

        horizontalLayout->addWidget(namelabel);

        agelabel = new QLabel(widget);
        agelabel->setObjectName("agelabel");

        horizontalLayout->addWidget(agelabel);


        retranslateUi(Hemodialysis_Dialog);

        QMetaObject::connectSlotsByName(Hemodialysis_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Hemodialysis_Dialog)
    {
        Hemodialysis_Dialog->setWindowTitle(QCoreApplication::translate("Hemodialysis_Dialog", "Dialog", nullptr));
        btn_check->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\207\252\346\243\200", nullptr));
        btn_claen->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\206\234\346\270\205\346\264\227", nullptr));
        btn_connectD->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\277\236\346\216\245\345\212\250\350\204\211\347\253\257", nullptr));
        btn_connectJ->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\277\236\346\216\245\351\235\231\350\204\211\347\253\257", nullptr));
        btn_open->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\346\211\223\345\274\200\350\241\200\346\263\265", nullptr));
        btn_fill->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\351\200\217\346\236\220\346\266\262\345\241\253\345\205\205", nullptr));
        btn_start->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\345\274\200\345\247\213\351\200\217\346\236\220", nullptr));
        btn_emergency->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\347\264\247\346\200\245", nullptr));
        btn_quit->setText(QString());
        label_3->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\351\200\217\346\236\220\346\266\262", nullptr));
        label_4->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\256\276\347\275\256\350\241\200\346\263\265\346\265\201\351\200\237", nullptr));
        lab_e->setText(QCoreApplication::translate("Hemodialysis_Dialog", "TextLabel", nullptr));
        namelabel->setText(QCoreApplication::translate("Hemodialysis_Dialog", "TextLabel", nullptr));
        agelabel->setText(QCoreApplication::translate("Hemodialysis_Dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hemodialysis_Dialog: public Ui_Hemodialysis_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEMODIALYSIS_DIALOG_H
