#include "hemodialysis_dialog.h"
#include "ui_hemodialysis_dialog.h"
#include <QDebug>
#include <QTimer>
#include "user_data.h"
extern User_Data user;

Hemodialysis_Dialog::Hemodialysis_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hemodialysis_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("血透仪"));
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
    serialPortInit();
}

Hemodialysis_Dialog::~Hemodialysis_Dialog()
{
    if (m_serial) {
        m_serial->serialClose();
        delete m_serial;
    }
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

void Hemodialysis_Dialog::serialPortInit()
{
    m_serial = new Serial_Tool();
    m_serial->m_serialport = new QSerialPort(this);
    m_serial->serialOpen("COM2");
    connect(m_serial->m_serialport, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void Hemodialysis_Dialog::receiveData()
{
    QByteArray data = m_serial->m_serialport->readAll();
    QString strData = QString::fromLocal8Bit(data);
    QStringList parts = strData.split(':');
    if (parts.size() >= 3 && parts[0] == "HDD") {
        QString command = parts[1];
        int progress = parts[2].toInt();
        updateHemoProgress(command, progress);
    }
}

void Hemodialysis_Dialog::updateHemoProgress(QString command, int progress)
{
    if (command == "check") {
        ui->progressBar_check->setValue(progress);
        if (progress >= 100) {
            ui->btn_claen->setEnabled(1);
        }
    } else if (command == "clean") {
        ui->progressBar_clean->setValue(progress);
        if (progress >= 100) {
            ui->btn_connectD->setEnabled(1);
        }
    } else if (command == "connectD") {
        ui->progressBar_D->setValue(progress);
        if (progress >= 100) {
            ui->btn_connectJ->setEnabled(1);
        }
    } else if (command == "connectJ") {
        ui->progressBar_J->setValue(progress);
        if (progress >= 100) {
            ui->btn_open->setEnabled(1);
        }
    } else if (command == "open") {
        ui->progressBar_blood->setValue(progress);
        if (progress >= 100) {
            ui->btn_fill->setEnabled(1);
        }
    } else if (command == "fill") {
        m_fillBar->setValue(progress);
        if (progress >= 100) {
            ui->btn_start->setEnabled(1);
        }
    } else if (command == "start") {
        m_startBar->setValue(progress);
    }
}

void Hemodialysis_Dialog::on_btn_open_clicked()
{
    m_currentCommand = "open";
    m_serial->m_serialport->write("HDD:open");
}

void Hemodialysis_Dialog::on_btn_connectJ_clicked()
{
    m_currentCommand = "connectJ";
    m_serial->m_serialport->write("HDD:connectJ");
}

void Hemodialysis_Dialog::on_btn_connectD_clicked()
{
    m_currentCommand = "connectD";
    m_serial->m_serialport->write("HDD:connectD");
}

void Hemodialysis_Dialog::on_btn_claen_clicked()
{
    m_currentCommand = "clean";
    m_serial->m_serialport->write("HDD:clean");
}

void Hemodialysis_Dialog::on_btn_fill_clicked()
{
    m_currentCommand = "fill";
    m_serial->m_serialport->write("HDD:fill");
}

void Hemodialysis_Dialog::on_btn_start_clicked()
{
    m_currentCommand = "start";
    m_serial->m_serialport->write("HDD:start");
}

void Hemodialysis_Dialog::on_btn_emergency_clicked()
{
    m_serial->m_serialport->write("HDD:emergency");
    ui->lab_e->setStyleSheet("background-color: rgb(255, 0, 0);");
}

void Hemodialysis_Dialog::on_btn_check_clicked()
{
    m_currentCommand = "check";
    m_serial->m_serialport->write("HDD:check");
}

void Hemodialysis_Dialog::on_btn_quit_clicked()
{
    close();
}

void Hemodialysis_Dialog::updateProgress()
{
}
