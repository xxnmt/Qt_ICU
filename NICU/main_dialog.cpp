#include "main_dialog.h"
#include "ui_main_dialog.h"

Main_Dialog::Main_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Main_Dialog)
{
    ui->setupUi(this);
    // 防止主窗口缓冲区残留黑块
    setAutoFillBackground(true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);

    // 如果你的主窗口是无边框透明，必须加这一段
    /*
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QColor("#ffffff")); // 和UI底色一致
    setPalette(pal);
    */
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
    BloodPressure_Dialog *bpDialog = new BloodPressure_Dialog();
    bpDialog->show();
}


void Main_Dialog::on_btn_Blood_clicked()
{
    Hemodialysis_Dialog *hemoDialog = new Hemodialysis_Dialog();
    hemoDialog->show();
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




