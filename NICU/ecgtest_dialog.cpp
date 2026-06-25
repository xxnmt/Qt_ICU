#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QVector>
#include <QFont>

#include "ecgtest_dialog.h"
#include "ui_ecgtest_dialog.h"
#include "user_data.h"


#define DOTS 5

User_Data user(QString::fromLocal8Bit("张依然"),25);

ECGTest_Dialog::ECGTest_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ECGTest_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("心电图"));
    setWindowFlags(Qt::FramelessWindowHint);

    ui->label_UserAge->setText(QString::number(user.getAge()));
    ui->label_UserName->setText(user.getName());

    QString fileName = ":/resource/heartData/hisdata.txt";
    User_serialflag = false;

    readECGFile(fileName);

    serialPortInit();
}

ECGTest_Dialog::~ECGTest_Dialog()
{
    delete ui;
}

void ECGTest_Dialog::readECGFile(QString FileName)
{
    int cols =2,rows =6;
    for(int col=0;col<cols;col++)
    {
        for(int row=0;row<rows;row++)
        {
            Heart_Data *tmpHeartData = new Heart_Data();
            QJsonObject edata = User_DataArr.at(col*rows+row).toObject();
            QString channelName =edata["channel"].toString();
            QJsonArray dataArr = edata["value"].toArray();

            tmpHeartData->setChannelName(channelName);
            tmpHeartData->setDataArr(dataArr);

            User_ChannelData[col*rows+row] = tmpHeartData;

        }

    }
}

void ECGTest_Dialog::getHistoryData()
{
    int cols =2,rows =6;
    for(int col=0;col<cols;col++)
    {
        for(int row=0;row<rows;row++)
        {
            Heart_Data *tmpHeartData = new Heart_Data();
            QJsonObject edata = User_DataArr.at(col*rows+row).toObject();
            QString channelName =edata["channel"].toString();
            QJsonArray dataArr = edata["value"].toArray();

            tmpHeartData->setChannelName(channelName);
            tmpHeartData->setDataArr(dataArr);

            User_ChannelData[col*rows+row] = tmpHeartData;

        }

    }

}

void ECGTest_Dialog::paintEvent(QPaintEvent *event)
{
    int w = this->width();
    int h = this->height();
    int channelnum = sizeof(User_ChannelData)/sizeof(Heart_Data *);
    QPainter painter(this);

    drawHisECGWave(painter,w,h,DOTS);
    if(User_serialflag)
    {
        updateECGWave(painter,w,h,DOTS);
    }
    painter.save();
    QFont f("微软雅黑");
    f.setBold(true);
    painter.setFont(f);
    painter.setPen(QColor(0,102,227));
    QString text = QString("Channel:%1  Speed:25mm/s").arg(channelnum);
    painter.drawText(10,13, text);
    painter.restore();
}

void ECGTest_Dialog::drawECGGrid(QPainter &painter, int width, int height, double dots)
{
    painter.save();
    painter.setPen(QColor(247,250,250));
    for(int i=0;i<=width/DOTS;i++)
    {
        painter.drawLine(0,i*DOTS,width,i*DOTS);//row
        painter.drawLine(i*DOTS, 0, i*DOTS ,height);//col
    }
    painter.setPen(QColor(206,224,229));
    for(int i=0;i<=width/DOTS/5;i++)
    {
        painter.drawLine(0,i*DOTS*5,width,i*DOTS*5);//row
        painter.drawLine(i*DOTS*5, 0, i*DOTS*5 ,height);//col
    }
    painter.restore();
}

void ECGTest_Dialog::drawHisECGWave(QPainter &painter, int width, int height, double dots)
{
    QPixmap *pixmap = new QPixmap(this->size());
    pixmap->fill(Qt::white);
    painter.drawPixmap(0,0,*pixmap,0,0,0,0);
    drawECGGrid(painter,width,height,dots);

    for(int i=0;i<12;i++)
    {
        QString data = QString::fromLocal8Bit(User_newdata.at(i));
        User_ChannelData[i]->addData(data.toInt());

    }
    painter.save();
    float fpPerMv = 10*dots;
    float fpPerUv = 0.001*fpPerMv;
    int rectWidth = width/2;
    int rowHeight = height/6;
    int middleHeight = rowHeight/2;
    int cols = 2;
    int rows = 6;
    for(int col=0;col<cols;col++)
    {
        for(int row=0;row<rows;row++)
        {
            QString channelName = User_ChannelData[col*rows+row]->getChannelName();
            QJsonArray dataArr = User_ChannelData[col*rows+row]->getDataArr();

            int wavelength = dataArr.size();
            QVector<QPointF> vecPoints;
            for(int i=0;i<wavelength;i++)
            {
                if(i>rectWidth-dots*2)
                    break;
                QPointF p(col*rectWidth + i,row*rowHeight+middleHeight-dataArr[i].toInt()*fpPerUv+25);
                vecPoints.append(p);
            }

            painter.save();
            painter.setPen(QColor(62,168,115));
            painter.drawText(col*rectWidth,row*rowHeight+middleHeight+25,channelName);
            painter.restore();

            for(int i=0; i<vecPoints.size()-1;++i)
            {
                painter.drawLine(vecPoints[i],vecPoints[i+1]);
            }
        }
    }
    //qDebug()<<"updateECGWave";
    painter.restore();

}

bool ECGTest_Dialog::serialPortInit()
{
    User_serial = new Serial_Tool();
    User_serial->m_serialport = new QSerialPort();

    connect(User_serial->m_serialport,SIGNAL(readyRead()),this,SLOT(receiveData()));

    if(User_serial->serialOpen())
        return true;
    else
        return false;

}

void ECGTest_Dialog::updateECGWave(QPainter &painter, int width, int height, double dots)
{
    QPixmap *pixmap = new QPixmap(this->size());
    pixmap->fill(Qt::white);
    painter.drawPixmap(0,0,*pixmap,0,0,0,0);
    drawECGGrid(painter,width,height,dots);

    for(int i=0;i<12;i++)
    {
        if(i < User_newdata.size()) {
            QString data = QString::fromLocal8Bit(User_newdata.at(i));
            User_ChannelData[i]->addData(data.toInt());
        }
    }
    painter.save();
    float fpPerMv = 10*dots;
    float fpPerUv = 0.001*fpPerMv;
    int rectWidth = width/2;
    int rowHeight = height/6;
    int middleHeight = rowHeight/2;
    int cols = 2;
    int rows = 6;
    for(int col=0;col<cols;col++)
    {
        for(int row=0;row<rows;row++)
        {
            QString channelName = User_ChannelData[col*rows+row]->getChannelName();
            QJsonArray dataArr = User_ChannelData[col*rows+row]->getDataArr();

            int wavelength = dataArr.size();
            QVector<QPointF> vecPoints;
            for(int i=0;i<wavelength;i++)
            {
                if(i>rectWidth-dots*2)
                    break;
                QPointF p(col*rectWidth + i,row*rowHeight+middleHeight-dataArr[i].toInt()*fpPerUv+25);
                vecPoints.append(p);
            }

            painter.save();
            painter.setPen(QColor(62,168,115));
            painter.drawText(col*rectWidth,row*rowHeight+middleHeight+25,channelName);
            painter.restore();

            for(int i=0; i<vecPoints.size()-1;++i)
            {
                painter.drawLine(vecPoints[i],vecPoints[i+1]);
            }
        }
    }
    //qDebug()<<"updateECGWave";
    painter.restore();

}

void ECGTest_Dialog::on_btn_quit_clicked()
{
    User_serial->serialClose();
    close();

}

void ECGTest_Dialog::receiveData()
{
    QByteArray message = User_serial->m_serialport->readAll();
    User_newdata = message.split(',');
    User_serialflag = true;
    repaint();

}

