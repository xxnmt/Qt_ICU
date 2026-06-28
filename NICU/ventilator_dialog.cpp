#include "ventilator_dialog.h"
#include "ui_ventilator_dialog.h"
#include "ventilator_dialog.h"
#include "ui_ventilator_dialog.h"
#include <QTimer>
#include <QMovie>
#include <QObject>
extern User_Data user;


Ventilator_Dialog::Ventilator_Dialog(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Ventilator_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("呼吸机"));
    // setWindowFlags(Qt::FramelessWindowHint);
    ui->lab_name->setText(user.getName());
    ui->lab_age->setText(QString::number(user.getAge()));
    m_lock = 1;
    showGif();
    serialportInit();
    alarmLight();

}

Ventilator_Dialog::~Ventilator_Dialog()
{
    m_serial->serialClose();
    delete ui;
}

void Ventilator_Dialog::showGif()
{
    QMovie *movie=new QMovie(":/resource_inside/images/breathgif.gif");
    ui->lab_Gif->setMovie(movie);

    ui->lab_Gif->setScaledContents(true);
    movie->start();
}

void Ventilator_Dialog::showInfo(QByteArray info)
{
    QList<QByteArray>data=info.split(',');
    ui->num_wet->display(data.at(0));
    ui->num_leak->display(data.at(1));

}

bool Ventilator_Dialog::serialportInit()
{
    m_serial =new Serial_Tool;
    m_serial->m_serialport=new QSerialPort();
    connect(m_serial->m_serialport,SIGNAL(readyRead()),this,SLOT(receiveDataa()));
    m_serial->serialOpen("com4");
    return 1;
}

void Ventilator_Dialog::alarmLight()
{
    ui->widget_light->setBackgroundColor(QColor(23,186,154));
    m_lightState = 0;
    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer,SIGNAL(timeout()),this, SLOT(updateLight()));
    m_timer->start();
}

void Ventilator_Dialog::on_btn_lock_clicked()
{
    if(m_lock){
        ui->btn_lock->setStyleSheet(
            "QPushButton {"
            "    border-image: url(:/resource_inside/images/unlock.png);"
            "    border: none;"
            "}"
            );
        m_lock=0;
    }
    else{
        ui->btn_lock->setStyleSheet(
            "QPushButton {"
            "    border-image: url(:/resource_inside/images/lock.png);"
            "    border: none;"
            "}"
            );
        m_lock=1;
    }
}


void Ventilator_Dialog::on_btn_quit_clicked()
{
    m_timer->stop();
    m_serial->serialClose();
    close();
}

void Ventilator_Dialog::updateLight()
{
    if(m_lightState==0)
    {
        ui->widget_light->setGreenLight();
        m_lightState =1;
    }
    else if(m_lightState ==1)
    {
        ui->widget_light->setYellowLight();
        m_lightState=0;
    }
    else if(m_lightState == 2)
    {
        ui->widget_light->setRedLight();
        m_lightState =3;
    }
    else if(m_lightState ==3)
    {
        ui->widget_light->setOrangeLight();
        m_lightState =2;
    }
}

void Ventilator_Dialog::receiveDataa()
{
    QByteArray message;
    message.append(m_serial->m_serialport->readAll());
    if(message.at(0)=='e'){
        m_lightState=2;
    }
    else{
        showInfo(message);
    }
    message.clear();
}

