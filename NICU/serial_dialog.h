#ifndef SERIAL_DIALOG_H
#define SERIAL_DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Serial_Dialog;
}

class Serial_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Serial_Dialog(QWidget *parent = 0);
    ~Serial_Dialog();
    bool serialport_init();
    void timerEvent(QTimerEvent *event);

private slots:
    void on_serialControl_clicked();
    void on_heartTestBtn_clicked();

    void on_bloodPressureBtn_clicked();

    void on_breathTestBtn_clicked();

    void on_hurryBtn_clicked();

private:
    Ui::Serial_Dialog *ui;
    QSerialPort *m_serialport;
    int timeId;
    int timeIdHeart;
    int timeIdBreath;
    int timeIdPressure;
    int state;
};

#endif // SERIAL_DIALOG_H