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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hemodialysis_Dialog
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_check;
    QProgressBar *progressBar_check;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_claen;
    QProgressBar *progressBar_clean;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btn_connectD;
    QProgressBar *progressBar_D;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *btn_connectJ;
    QProgressBar *progressBar_J;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *btn_open;
    QProgressBar *progressBar_blood;
    QFormLayout *formLayout;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *namelabel;
    QLabel *agelabel;
    QPushButton *btn_quit;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btn_fill;
    QPushButton *btn_start;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lab_e;
    QPushButton *btn_emergency;

    void setupUi(QDialog *Hemodialysis_Dialog)
    {
        if (Hemodialysis_Dialog->objectName().isEmpty())
            Hemodialysis_Dialog->setObjectName("Hemodialysis_Dialog");
        Hemodialysis_Dialog->resize(750, 460);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Hemodialysis_Dialog->sizePolicy().hasHeightForWidth());
        Hemodialysis_Dialog->setSizePolicy(sizePolicy);
        Hemodialysis_Dialog->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(Hemodialysis_Dialog);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 0, 10, 10);
        widget = new QWidget(Hemodialysis_Dialog);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, 10, 10, 10);
        btn_check = new QPushButton(widget);
        btn_check->setObjectName("btn_check");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_check->sizePolicy().hasHeightForWidth());
        btn_check->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(btn_check);

        progressBar_check = new QProgressBar(widget);
        progressBar_check->setObjectName("progressBar_check");
        sizePolicy1.setHeightForWidth(progressBar_check->sizePolicy().hasHeightForWidth());
        progressBar_check->setSizePolicy(sizePolicy1);
        progressBar_check->setValue(24);

        horizontalLayout_2->addWidget(progressBar_check);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(10, 10, 10, 10);
        btn_claen = new QPushButton(widget);
        btn_claen->setObjectName("btn_claen");
        sizePolicy1.setHeightForWidth(btn_claen->sizePolicy().hasHeightForWidth());
        btn_claen->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(btn_claen);

        progressBar_clean = new QProgressBar(widget);
        progressBar_clean->setObjectName("progressBar_clean");
        sizePolicy1.setHeightForWidth(progressBar_clean->sizePolicy().hasHeightForWidth());
        progressBar_clean->setSizePolicy(sizePolicy1);
        progressBar_clean->setValue(24);

        horizontalLayout_8->addWidget(progressBar_clean);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(10, 10, 10, 10);
        btn_connectD = new QPushButton(widget);
        btn_connectD->setObjectName("btn_connectD");
        sizePolicy1.setHeightForWidth(btn_connectD->sizePolicy().hasHeightForWidth());
        btn_connectD->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(btn_connectD);

        progressBar_D = new QProgressBar(widget);
        progressBar_D->setObjectName("progressBar_D");
        sizePolicy1.setHeightForWidth(progressBar_D->sizePolicy().hasHeightForWidth());
        progressBar_D->setSizePolicy(sizePolicy1);
        progressBar_D->setValue(24);

        horizontalLayout_9->addWidget(progressBar_D);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(10, 10, 10, 10);
        btn_connectJ = new QPushButton(widget);
        btn_connectJ->setObjectName("btn_connectJ");
        sizePolicy1.setHeightForWidth(btn_connectJ->sizePolicy().hasHeightForWidth());
        btn_connectJ->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(btn_connectJ);

        progressBar_J = new QProgressBar(widget);
        progressBar_J->setObjectName("progressBar_J");
        sizePolicy1.setHeightForWidth(progressBar_J->sizePolicy().hasHeightForWidth());
        progressBar_J->setSizePolicy(sizePolicy1);
        progressBar_J->setValue(24);

        horizontalLayout_10->addWidget(progressBar_J);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(10, 10, 10, 10);
        btn_open = new QPushButton(widget);
        btn_open->setObjectName("btn_open");
        sizePolicy1.setHeightForWidth(btn_open->sizePolicy().hasHeightForWidth());
        btn_open->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(btn_open);

        progressBar_blood = new QProgressBar(widget);
        progressBar_blood->setObjectName("progressBar_blood");
        sizePolicy1.setHeightForWidth(progressBar_blood->sizePolicy().hasHeightForWidth());
        progressBar_blood->setSizePolicy(sizePolicy1);
        progressBar_blood->setValue(24);

        horizontalLayout_11->addWidget(progressBar_blood);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_11);


        verticalLayout_2->addLayout(verticalLayout);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(12);
        formLayout->setVerticalSpacing(12);
        formLayout->setContentsMargins(10, 10, 10, 10);
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_3);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, comboBox);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(100);
        spinBox->setMaximum(300);
        spinBox->setValue(180);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spinBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(2, QFormLayout::ItemRole::FieldRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(0, QFormLayout::ItemRole::FieldRole, verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(4, QFormLayout::ItemRole::FieldRole, verticalSpacer_3);


        verticalLayout_2->addLayout(formLayout);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(Hemodialysis_Dialog);
        widget_2->setObjectName("widget_2");
        verticalLayout_7 = new QVBoxLayout(widget_2);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(10, 0, 10, 10);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, -1, 10, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        namelabel = new QLabel(widget_2);
        namelabel->setObjectName("namelabel");
        sizePolicy1.setHeightForWidth(namelabel->sizePolicy().hasHeightForWidth());
        namelabel->setSizePolicy(sizePolicy1);
        namelabel->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";\n"
"color: rgb(255, 158, 200);\n"
""));

        horizontalLayout_3->addWidget(namelabel);

        agelabel = new QLabel(widget_2);
        agelabel->setObjectName("agelabel");
        sizePolicy1.setHeightForWidth(agelabel->sizePolicy().hasHeightForWidth());
        agelabel->setSizePolicy(sizePolicy1);
        agelabel->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";\n"
"color: rgb(248, 166, 255);"));

        horizontalLayout_3->addWidget(agelabel);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        btn_quit = new QPushButton(widget_2);
        btn_quit->setObjectName("btn_quit");
        sizePolicy.setHeightForWidth(btn_quit->sizePolicy().hasHeightForWidth());
        btn_quit->setSizePolicy(sizePolicy);
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/back.png);\n"
"width:25px;\n"
"height:25px;\n"
""));

        horizontalLayout_4->addWidget(btn_quit);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");

        horizontalLayout_5->addLayout(gridLayout);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(12);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        btn_fill = new QPushButton(widget_2);
        btn_fill->setObjectName("btn_fill");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_fill->sizePolicy().hasHeightForWidth());
        btn_fill->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(btn_fill);

        btn_start = new QPushButton(widget_2);
        btn_start->setObjectName("btn_start");
        sizePolicy2.setHeightForWidth(btn_start->sizePolicy().hasHeightForWidth());
        btn_start->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(btn_start);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 4);
        verticalLayout_6->setStretch(2, 1);

        verticalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(12);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(12);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(10, 10, 10, 10);
        lab_e = new QLabel(widget_2);
        lab_e->setObjectName("lab_e");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lab_e->sizePolicy().hasHeightForWidth());
        lab_e->setSizePolicy(sizePolicy3);
        lab_e->setMinimumSize(QSize(40, 40));
        lab_e->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_7->addWidget(lab_e);

        btn_emergency = new QPushButton(widget_2);
        btn_emergency->setObjectName("btn_emergency");
        sizePolicy1.setHeightForWidth(btn_emergency->sizePolicy().hasHeightForWidth());
        btn_emergency->setSizePolicy(sizePolicy1);
        btn_emergency->setMaximumSize(QSize(100, 20));
        btn_emergency->setStyleSheet(QString::fromUtf8("width:100px;\n"
"background-color: rgb(0, 0, 0);"));

        horizontalLayout_7->addWidget(btn_emergency);

        horizontalLayout_7->setStretch(0, 4);
        horizontalLayout_7->setStretch(1, 1);

        verticalLayout_8->addLayout(horizontalLayout_7);

        verticalLayout_8->setStretch(0, 2);

        verticalLayout_7->addLayout(verticalLayout_8);

        verticalLayout_7->setStretch(0, 1);
        verticalLayout_7->setStretch(1, 2);

        horizontalLayout->addWidget(widget_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


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
        label_3->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\351\200\217\346\236\220\346\266\262", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Hemodialysis_Dialog", "A\346\266\262", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Hemodialysis_Dialog", "B\346\266\262", nullptr));

        label_4->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\350\241\200\346\263\265\346\265\201\351\200\237", nullptr));
        namelabel->setText(QCoreApplication::translate("Hemodialysis_Dialog", "123", nullptr));
        agelabel->setText(QCoreApplication::translate("Hemodialysis_Dialog", "123", nullptr));
        btn_quit->setText(QString());
        btn_fill->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\351\200\217\346\236\220\346\266\262\345\241\253\345\205\205", nullptr));
        btn_start->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\345\274\200\345\247\213\351\200\217\346\236\220", nullptr));
        lab_e->setText(QString());
        btn_emergency->setText(QCoreApplication::translate("Hemodialysis_Dialog", "\347\264\247\346\200\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hemodialysis_Dialog: public Ui_Hemodialysis_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEMODIALYSIS_DIALOG_H
