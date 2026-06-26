/********************************************************************************
** Form generated from reading UI file 'main_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_DIALOG_H
#define UI_MAIN_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *btn_Heart;
    QPushButton *btn_Pressure;
    QPushButton *btn_Blood;
    QPushButton *btn_Breath;
    QLabel *lab_Heart;
    QLabel *lab_Blood;
    QLabel *lab_Pressure;
    QLabel *lab_Breath;
    QLabel *lab_Title;

    void setupUi(QDialog *Main_Dialog)
    {
        if (Main_Dialog->objectName().isEmpty())
            Main_Dialog->setObjectName("Main_Dialog");
        Main_Dialog->resize(760, 540);
        Main_Dialog->setStyleSheet(QString::fromUtf8("border-image: url(:/resource_inside/images/mainbanner.png);"));
        tabWidget = new QTabWidget(Main_Dialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 90, 760, 450));
        tabWidget->setStyleSheet(QString::fromUtf8("border: none;  /* \342\234\205 \347\247\273\351\231\244\350\276\271\346\241\206 */"));
        tab = new QWidget();
        tab->setObjectName("tab");
        tab->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/hospitalback.jpg);"));
        btn_Heart = new QPushButton(tab);
        btn_Heart->setObjectName("btn_Heart");
        btn_Heart->setGeometry(QRect(390, 40, 120, 120));
        btn_Heart->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/heart.png);"));
        btn_Pressure = new QPushButton(tab);
        btn_Pressure->setObjectName("btn_Pressure");
        btn_Pressure->setGeometry(QRect(390, 240, 120, 120));
        btn_Pressure->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/pressure.png);"));
        btn_Blood = new QPushButton(tab);
        btn_Blood->setObjectName("btn_Blood");
        btn_Blood->setGeometry(QRect(570, 40, 120, 120));
        btn_Blood->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/blood.png);"));
        btn_Breath = new QPushButton(tab);
        btn_Breath->setObjectName("btn_Breath");
        btn_Breath->setGeometry(QRect(570, 240, 120, 120));
        btn_Breath->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/breath.png);"));
        lab_Heart = new QLabel(tab);
        lab_Heart->setObjectName("lab_Heart");
        lab_Heart->setGeometry(QRect(420, 160, 60, 20));
        lab_Heart->setStyleSheet(QString::fromUtf8("border-image: none;\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"\n"
"font: 16pt \"Microsoft YaHei UI\";"));
        lab_Heart->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lab_Blood = new QLabel(tab);
        lab_Blood->setObjectName("lab_Blood");
        lab_Blood->setGeometry(QRect(610, 160, 70, 20));
        lab_Blood->setStyleSheet(QString::fromUtf8("border-image: none;\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"\n"
"font: 16pt \"Microsoft YaHei UI\";"));
        lab_Blood->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lab_Pressure = new QLabel(tab);
        lab_Pressure->setObjectName("lab_Pressure");
        lab_Pressure->setGeometry(QRect(420, 360, 70, 20));
        lab_Pressure->setStyleSheet(QString::fromUtf8("border-image: none;\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"\n"
"font: 16pt \"Microsoft YaHei UI\";"));
        lab_Pressure->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lab_Breath = new QLabel(tab);
        lab_Breath->setObjectName("lab_Breath");
        lab_Breath->setGeometry(QRect(610, 360, 70, 20));
        lab_Breath->setStyleSheet(QString::fromUtf8("border-image: none;\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"\n"
"font: 16pt \"Microsoft YaHei UI\";"));
        lab_Breath->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tabWidget->addTab(tab, QString());
        lab_Title = new QLabel(Main_Dialog);
        lab_Title->setObjectName("lab_Title");
        lab_Title->setGeometry(QRect(80, 10, 591, 91));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(36);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        lab_Title->setFont(font);
        lab_Title->setStyleSheet(QString::fromUtf8("border-image: none;\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);\n"
"font: 36pt \"Microsoft YaHei UI\";"));
        lab_Title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(Main_Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Main_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Main_Dialog)
    {
        Main_Dialog->setWindowTitle(QCoreApplication::translate("Main_Dialog", "Main_Dialog", nullptr));
        btn_Heart->setText(QString());
        btn_Pressure->setText(QString());
        btn_Blood->setText(QString());
        btn_Breath->setText(QString());
        lab_Heart->setText(QCoreApplication::translate("Main_Dialog", "\345\277\203\347\224\265\345\233\276", nullptr));
        lab_Blood->setText(QCoreApplication::translate("Main_Dialog", "\350\241\200\351\200\217\344\273\252", nullptr));
        lab_Pressure->setText(QCoreApplication::translate("Main_Dialog", "\350\241\200\345\216\213\344\273\252", nullptr));
        lab_Breath->setText(QCoreApplication::translate("Main_Dialog", "\345\221\274\345\220\270\346\234\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Main_Dialog", "Tab1", nullptr));
        lab_Title->setText(QCoreApplication::translate("Main_Dialog", "\351\207\215\347\227\207\347\233\221\346\212\244\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Main_Dialog: public Ui_Main_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_DIALOG_H
