#include "serial_tool.h"
#include "QDebug"

Serial_Tool::Serial_Tool() {}
bool Serial_Tool::serialOpen(QString com)
{
    m_serialport->setPortName(com);
    m_serialport->setBaudRate(QSerialPort::Baud115200);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setStopBits(QSerialPort::OneStop);
    if(m_serialport->open(QIODevice::ReadWrite))
    {
        qDebug()<<"serial open";
        return true;
    }
    else
        return false;

}
void Serial_Tool::serialClose()
{
    if(m_serialport->isOpen())
        m_serialport->close();
}
