#ifndef SERIAL_TOOL_H
#define SERIAL_TOOL_H


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Serial_Tool
{
public:
    Serial_Tool();
    bool serialOpen();
    void serialClose();
    QSerialPort *m_serialport;
};

#endif // SERIAL_TOOL_H
