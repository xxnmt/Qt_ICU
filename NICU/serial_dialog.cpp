#include "serial_dialog.h"
#include "ui_serial_dialog.h"


#include <QDebug>
int arrs[]={16,12,9,8,6,34,20,22,20,16,12,9,8,9,
              10,8,6,-1,2,-3,-7,-8 ,-7,-6,7,2,-1,1,
              9,9,10,8,6,-1,2,-3,-7,-8,-7,-6,-6,7,2,
              -1,1,9,-7,-8,-7,-6,7,2,-1,1,-1,2,-3,-7,
              -8 ,8,6,-7,2,-1,1,9,-101,-200,-120,-40,
              40,120,280,459,670,835,900,835,670,450,
              340,240,27,18,14,10,6};
const int LENGTH = sizeof(arrs)/sizeof(int);
int index=0;
Serial_Dialog::Serial_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serial_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("数据传输客户端"));
    serialport_init();
    timeId = 0;
    timeIdHeart = 0;
    timeIdBreath = 0;
    timeIdPressure = 0;
    m_serialport = new QSerialPort();

}

Serial_Dialog::~Serial_Dialog()
{
    delete ui;
}
void Serial_Dialog::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timeIdPressure)
    {
        QByteArray message;
        unsigned char hp = (unsigned char)(120+rand()%10);
        unsigned char lp = (unsigned char)(80+rand()%5);
        unsigned char pulse = (unsigned char)(65+rand()%5);

        message.append(hp);
        message.append(lp);
        message.append(pulse);
        m_serialport->write(message);

    }
    else if(event->timerId()== timeIdHeart)
    {
        QByteArray msg;
        QString strnums;
        int nums[12];
        for(int i=0;i<12;i++)
        {
            nums[i]=arrs[index]+(unsigned)rand()%7;
            strnums.append(QString::number(nums[i])+",");
        }//17,19,20,17,18,...
        index++;
        if(index==LENGTH)
            index=0;
        msg.append(strnums.toUtf8());
        m_serialport->write(msg);
    }
    else if(event->timerId()== timeIdBreath)
    {
        QByteArray message;
        float num1 = 140+rand()%10*1.2;
        float num2 = 20 +rand()%5*1.2;
        QString nums = QString::number(num1,'f',1)+","+ QString::number(num2,'f',1);
        message.append(nums.toUtf8());         m_serialport->write(message);
    }
}
bool Serial_Dialog::serialport_init()
{
    QList<QSerialPortInfo> serialPortInfoList = QSerialPortInfo::availablePorts();
    if(serialPortInfoList.isEmpty())
        return false;
    QList<QSerialPortInfo>::iterator iter = serialPortInfoList.begin();
    while(iter!=serialPortInfoList.end())
    {
        ui->comboBox->addItem(iter->portName());
        iter++;
    }
}
void Serial_Dialog::on_serialControl_clicked()
{
    if(m_serialport->isOpen())
    {
        m_serialport->clear();
        m_serialport->close();
        ui->serialControl->setText(QString::fromLocal8Bit("打开串口"));
        ui->label->setStyleSheet("background-color:rgb(255,0,0);border-radius:12px;");
        if(timeIdHeart!=0)
        {
            killTimer(timeIdHeart);
            timeIdHeart = 0;
            index=0;
        }
        if(timeIdBreath!=0)
        {
            killTimer(timeIdBreath);
            timeIdBreath = 0;
        }
        if(timeIdPressure!=0)
        {
            killTimer(timeIdPressure);
            timeIdPressure = 0;
        }
    }
    else
    {
        m_serialport->setPortName(ui->comboBox->currentText());
        m_serialport->setBaudRate(QSerialPort::Baud115200);
        m_serialport->setDataBits(QSerialPort::Data8);
        m_serialport->setParity(QSerialPort::NoParity);
        m_serialport->setStopBits(QSerialPort::OneStop);
        m_serialport->open(QIODevice::ReadWrite);
        ui->serialControl->setText(QString::fromLocal8Bit("关闭串口"));
        ui->label->setStyleSheet("background-color:rgb(0,255,0);border-radius:12px;");
    }
}

void Serial_Dialog::on_heartTestBtn_clicked()
{
    timeIdHeart = startTimer(200);
}

void Serial_Dialog::on_bloodPressureBtn_clicked()
{
    timeIdPressure = startTimer(1000);
}

void Serial_Dialog::on_breathTestBtn_clicked()
{
    timeIdBreath = startTimer(1000);
}

void Serial_Dialog::on_hurryBtn_clicked()
{
    m_serialport->write("e");
}

