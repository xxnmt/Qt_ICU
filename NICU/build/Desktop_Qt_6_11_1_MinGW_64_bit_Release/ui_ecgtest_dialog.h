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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ECGTest_Dialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_UserName;
    QLabel *label_UserAge;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_quit;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ECGTest_Dialog)
    {
        if (ECGTest_Dialog->objectName().isEmpty())
            ECGTest_Dialog->setObjectName("ECGTest_Dialog");
        ECGTest_Dialog->resize(750, 460);
        ECGTest_Dialog->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(ECGTest_Dialog);
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_UserName = new QLabel(ECGTest_Dialog);
        label_UserName->setObjectName("label_UserName");
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        label_UserName->setFont(font);
        label_UserName->setStyleSheet(QString::fromUtf8("\n"
"font: 14pt \"Microsoft YaHei UI\";"));

        horizontalLayout->addWidget(label_UserName);

        label_UserAge = new QLabel(ECGTest_Dialog);
        label_UserAge->setObjectName("label_UserAge");
        label_UserAge->setFont(font);
        label_UserAge->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";"));

        horizontalLayout->addWidget(label_UserAge);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btn_quit = new QPushButton(ECGTest_Dialog);
        btn_quit->setObjectName("btn_quit");
        btn_quit->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/images/back.png);\n"
"width:25px;\n"
"height:25px"));

        horizontalLayout_2->addWidget(btn_quit);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);


        retranslateUi(ECGTest_Dialog);

        QMetaObject::connectSlotsByName(ECGTest_Dialog);
    } // setupUi

    void retranslateUi(QDialog *ECGTest_Dialog)
    {
        ECGTest_Dialog->setWindowTitle(QCoreApplication::translate("ECGTest_Dialog", "Dialog", nullptr));
        label_UserName->setText(QCoreApplication::translate("ECGTest_Dialog", "TextLabel", nullptr));
        label_UserAge->setText(QCoreApplication::translate("ECGTest_Dialog", "TextLabel", nullptr));
        btn_quit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ECGTest_Dialog: public Ui_ECGTest_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECGTEST_DIALOG_H
