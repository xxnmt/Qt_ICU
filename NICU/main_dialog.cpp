#include "main_dialog.h"
#include "ui_main_dialog.h"

Main_Dialog::Main_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Main_Dialog)
{
    ui->setupUi(this);
}

Main_Dialog::~Main_Dialog()
{
    delete ui;
}

void Main_Dialog::on_btn_Heart_clicked()
{
    ECGTest_Dialog *ecgDialog = new ECGTest_Dialog();
    ecgDialog->show();
}


void Main_Dialog::on_btn_Pressure_clicked()
{
    // BloodPressure_Dialog *bpDialog = new BloodPressure_Dialog();
    // bpDialog->show();
}


void Main_Dialog::on_btn_Blood_clicked()
{
    // Hemodialysis_Dialog *hemoDialog = new Hemodialysis_Dialog();
    // hemoDialog->show();
}


void Main_Dialog::on_btn_Quit_clicked()
{
    close();
}


void Main_Dialog::on_btn_Breath_clicked()
{
    // Ventilator_Dialog *vDialog = new Ventilator_Dialog();
    // vDialog->show();
}


void Main_Dialog::on_pushButton_clicked()
{
    Serial_Dialog* ser=new Serial_Dialog();
    ser->show();
}

