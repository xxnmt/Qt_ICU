/********************************************************************************
** Form generated from reading UI file 'ventilator_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTILATOR_DIALOG_H
#define UI_VENTILATOR_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "alarm_light.h"

QT_BEGIN_NAMESPACE

class Ui_Ventilator_Dialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lab_name;
    QLabel *lab_age;
    QPushButton *btn_quit;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_15;
    QPushButton *btn_lock;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QLCDNumber *num_wet;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLCDNumber *num_leak;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLCDNumber *num_air_min;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QLCDNumber *num_breathingRate;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QLCDNumber *num_breathingTime;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    Alarm_Light *widget_light;
    QWidget *widget;
    QLabel *lab_Gif;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout_3;
    QLabel *label_13;
    QLabel *label_2;
    QLabel *label_14;
    QLCDNumber *numboostTime;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QLCDNumber *num_IPAP;
    QLabel *label_10;
    QLCDNumber *num_EPAP;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLCDNumber *num_backupRate;
    QLabel *label_6;
    QLCDNumber *num_IERO;

    void setupUi(QDialog *Ventilator_Dialog)
    {
        if (Ventilator_Dialog->objectName().isEmpty())
            Ventilator_Dialog->setObjectName("Ventilator_Dialog");
        Ventilator_Dialog->resize(750, 460);
        gridLayout = new QGridLayout(Ventilator_Dialog);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lab_name = new QLabel(Ventilator_Dialog);
        lab_name->setObjectName("lab_name");

        horizontalLayout_3->addWidget(lab_name);

        lab_age = new QLabel(Ventilator_Dialog);
        lab_age->setObjectName("lab_age");

        horizontalLayout_3->addWidget(lab_age);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        btn_quit = new QPushButton(Ventilator_Dialog);
        btn_quit->setObjectName("btn_quit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_quit->sizePolicy().hasHeightForWidth());
        btn_quit->setSizePolicy(sizePolicy);
        btn_quit->setMinimumSize(QSize(25, 25));
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource_inside/images/back.png);"));

        horizontalLayout_4->addWidget(btn_quit);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_15 = new QLabel(Ventilator_Dialog);
        label_15->setObjectName("label_15");

        verticalLayout_6->addWidget(label_15);

        btn_lock = new QPushButton(Ventilator_Dialog);
        btn_lock->setObjectName("btn_lock");
        sizePolicy.setHeightForWidth(btn_lock->sizePolicy().hasHeightForWidth());
        btn_lock->setSizePolicy(sizePolicy);
        btn_lock->setMinimumSize(QSize(25, 30));
        btn_lock->setStyleSheet(QString::fromUtf8("border-image: url(:/resource_inside/images/lock.png);"));

        verticalLayout_6->addWidget(btn_lock);

        verticalLayout_6->setStretch(0, 2);
        verticalLayout_6->setStretch(1, 5);

        horizontalLayout_7->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(10, 10, 10, 10);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label = new QLabel(Ventilator_Dialog);
        label->setObjectName("label");

        verticalLayout_5->addWidget(label);

        num_wet = new QLCDNumber(Ventilator_Dialog);
        num_wet->setObjectName("num_wet");

        verticalLayout_5->addWidget(num_wet);


        horizontalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(Ventilator_Dialog);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);

        num_leak = new QLCDNumber(Ventilator_Dialog);
        num_leak->setObjectName("num_leak");

        verticalLayout_4->addWidget(num_leak);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_5 = new QLabel(Ventilator_Dialog);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        num_air_min = new QLCDNumber(Ventilator_Dialog);
        num_air_min->setObjectName("num_air_min");

        verticalLayout_3->addWidget(num_air_min);


        horizontalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_7 = new QLabel(Ventilator_Dialog);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        num_breathingRate = new QLCDNumber(Ventilator_Dialog);
        num_breathingRate->setObjectName("num_breathingRate");

        verticalLayout_2->addWidget(num_breathingRate);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_9 = new QLabel(Ventilator_Dialog);
        label_9->setObjectName("label_9");

        verticalLayout->addWidget(label_9);

        num_breathingTime = new QLCDNumber(Ventilator_Dialog);
        num_breathingTime->setObjectName("num_breathingTime");

        verticalLayout->addWidget(num_breathingTime);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout_7->addItem(horizontalSpacer_4);


        horizontalLayout_7->addLayout(verticalLayout_7);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 111);

        gridLayout->addLayout(horizontalLayout_7, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        widget_light = new Alarm_Light(Ventilator_Dialog);
        widget_light->setObjectName("widget_light");

        horizontalLayout_2->addWidget(widget_light);

        widget = new QWidget(Ventilator_Dialog);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(25, 25));
        lab_Gif = new QLabel(widget);
        lab_Gif->setObjectName("lab_Gif");
        lab_Gif->setGeometry(QRect(0, -10, 370, 250));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lab_Gif->sizePolicy().hasHeightForWidth());
        lab_Gif->setSizePolicy(sizePolicy1);
        lab_Gif->setMinimumSize(QSize(370, 250));

        horizontalLayout_2->addWidget(widget);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 2, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        label_13 = new QLabel(Ventilator_Dialog);
        label_13->setObjectName("label_13");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, label_13);

        label_2 = new QLabel(Ventilator_Dialog);
        label_2->setObjectName("label_2");

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, label_2);

        label_14 = new QLabel(Ventilator_Dialog);
        label_14->setObjectName("label_14");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::LabelRole, label_14);

        numboostTime = new QLCDNumber(Ventilator_Dialog);
        numboostTime->setObjectName("numboostTime");

        formLayout_3->setWidget(1, QFormLayout::ItemRole::FieldRole, numboostTime);


        horizontalLayout->addLayout(formLayout_3);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label_8 = new QLabel(Ventilator_Dialog);
        label_8->setObjectName("label_8");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label_8);

        num_IPAP = new QLCDNumber(Ventilator_Dialog);
        num_IPAP->setObjectName("num_IPAP");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, num_IPAP);

        label_10 = new QLabel(Ventilator_Dialog);
        label_10->setObjectName("label_10");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_10);

        num_EPAP = new QLCDNumber(Ventilator_Dialog);
        num_EPAP->setObjectName("num_EPAP");

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, num_EPAP);


        horizontalLayout->addLayout(formLayout_2);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_4 = new QLabel(Ventilator_Dialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_4);

        num_backupRate = new QLCDNumber(Ventilator_Dialog);
        num_backupRate->setObjectName("num_backupRate");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, num_backupRate);

        label_6 = new QLabel(Ventilator_Dialog);
        label_6->setObjectName("label_6");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_6);

        num_IERO = new QLCDNumber(Ventilator_Dialog);
        num_IERO->setObjectName("num_IERO");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, num_IERO);


        horizontalLayout->addLayout(formLayout);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 2);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 2);
        gridLayout->setRowStretch(2, 4);
        gridLayout->setRowStretch(3, 1);

        retranslateUi(Ventilator_Dialog);

        QMetaObject::connectSlotsByName(Ventilator_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Ventilator_Dialog)
    {
        Ventilator_Dialog->setWindowTitle(QCoreApplication::translate("Ventilator_Dialog", "Dialog", nullptr));
        lab_name->setText(QCoreApplication::translate("Ventilator_Dialog", "TextLabel", nullptr));
        lab_age->setText(QCoreApplication::translate("Ventilator_Dialog", "TextLabel", nullptr));
        btn_quit->setText(QString());
        label_15->setText(QCoreApplication::translate("Ventilator_Dialog", "\346\237\245\347\234\213", nullptr));
        btn_lock->setText(QString());
        label->setText(QCoreApplication::translate("Ventilator_Dialog", "\346\275\256\346\260\224\351\207\217", nullptr));
        label_3->setText(QCoreApplication::translate("Ventilator_Dialog", "\346\274\217\346\260\224\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("Ventilator_Dialog", "\346\257\217\345\210\206\351\222\237\351\200\232\346\260\224\351\207\217", nullptr));
        label_7->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\221\274\345\220\270\351\242\221\347\216\207", nullptr));
        label_9->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\220\270\346\260\224\346\227\266\351\227\264", nullptr));
        lab_Gif->setText(QString());
        label_13->setText(QCoreApplication::translate("Ventilator_Dialog", "\351\200\232\346\260\224\346\250\241\345\274\217", nullptr));
        label_2->setText(QCoreApplication::translate("Ventilator_Dialog", "TextLabel", nullptr));
        label_14->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\215\207\345\216\213\346\227\266\351\227\264", nullptr));
        label_8->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\220\270\346\260\224\345\216\213\345\212\233", nullptr));
        label_10->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\221\274\346\260\224\345\216\213\345\212\233", nullptr));
        label_4->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\244\207\347\224\250\351\242\221\347\216\207", nullptr));
        label_6->setText(QCoreApplication::translate("Ventilator_Dialog", "\345\221\274\345\220\270\346\257\224\344\276\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ventilator_Dialog: public Ui_Ventilator_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTILATOR_DIALOG_H
