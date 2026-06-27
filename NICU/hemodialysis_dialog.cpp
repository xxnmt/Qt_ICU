#include "hemodialysis_dialog.h"
#include "ui_hemodialysis_dialog.h"
#include <QDebug>
#include <QTimer>
#include "user_data.h"
int percent=0;
extern User_Data user;
Hemodialysis_Dialog::Hemodialysis_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hemodialysis_Dialog)
{
    ui->setupUi(this);

    // // ✅ 清空 lab_e 的样式表，防止显示黑色方块
    // ui->lab_e->setStyleSheet("");
    // ui->lab_e->clear();
////////////////////////该方式无用//////////////////////////////
    setWindowTitle(QString::fromLocal8Bit("血透仪"));
    //无边框
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->namelabel->setText(user.getName());
    ui->agelabel->setText(QString::number(user.getAge()));
    ui->btn_connectD->setEnabled(0);
    ui->btn_connectJ->setEnabled(0);
    ui->btn_open->setEnabled(0);
    ui->btn_claen->setEnabled(0);
    ui->progressBar_clean->setValue(0);
    ui->progressBar_D->setValue(0);
    ui->progressBar_J->setValue(0);
    ui->progressBar_blood->setValue(0);
    ui->progressBar_check->setValue(0);
    drawRoundProgress();
}

Hemodialysis_Dialog::~Hemodialysis_Dialog()
{
    delete ui;
}

void Hemodialysis_Dialog::drawRoundProgress()
{
    m_fillBar = new ProgressBar_Round(this);
    m_fillBar->setOutColor(QColor(235,244,249));
    m_fillBar->setInColor(QColor(175,209,224));
    ui->gridLayout->addWidget(m_fillBar,0,0);

    m_startBar = new ProgressBar_Round(this);
    m_startBar->setOutColor(QColor(249,220,220));
    m_startBar->setInColor(QColor(170,75,70));
    ui->gridLayout->addWidget(m_startBar,0,1);
}

void Hemodialysis_Dialog::on_btn_open_clicked()
{
    delete m_splash;
    m_splash=new ProgressBar_Splash(5000,ui->progressBar_blood,NULL);
    //progressbar_splash调用show()会出现黑框
    //m_splash->show();
}


void Hemodialysis_Dialog::on_btn_connectJ_clicked()
{
    delete m_splash;
    m_splash = new ProgressBar_Splash(5000,ui->progressBar_J,ui->btn_open);
    //m_splash->show();
}


void Hemodialysis_Dialog::on_btn_connectD_clicked()
{
    m_splash = new ProgressBar_Splash(5000,ui->progressBar_D,ui->btn_connectJ);
    //m_splash->show();
}

void Hemodialysis_Dialog::on_btn_claen_clicked()
{
    m_splash = new ProgressBar_Splash(5000,ui->progressBar_clean,ui->btn_connectD);
    //m_splash->show();
}


void Hemodialysis_Dialog::on_btn_fill_clicked()
{
    m_fillBar->setValue(100);
}


void Hemodialysis_Dialog::on_btn_start_clicked()
{
    m_startBar->setValue(100);
}


void Hemodialysis_Dialog::on_btn_emergency_clicked()
{
    ui->lab_e->setStyleSheet("border-image: url(:/resource_inside/images/blood.png);");
}


void Hemodialysis_Dialog::on_btn_check_clicked()
{
    //删除旧定时器
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
        m_timer=nullptr;
    }
    percent=0;

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this, SLOT(updateProgress()));
    m_timer->start(100);

}


void Hemodialysis_Dialog::on_btn_quit_clicked()
{
    close();
}

void Hemodialysis_Dialog::updateProgress()
{
    if(percent>=100)
    {
        m_timer->stop();
            ui->btn_claen->setEnabled(1);
        return;
    }
    else
        percent+=5;
    ui->progressBar_check->setValue(percent);
}


