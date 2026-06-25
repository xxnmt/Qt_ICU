#ifndef ECGTEST_DIALOG_H
#define ECGTEST_DIALOG_H

#include <QDialog>
#include <QJsonArray>
#include "heart_data.h"
#include "serial_tool.h"

namespace Ui {
class ECGTest_Dialog;
}

class ECGTest_Dialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ECGTest_Dialog *ui;
    QJsonArray User_DataArr;
    Heart_Data* User_ChannelData[12];
    Serial_Tool *User_serial;
    QList<QByteArray> User_newdata;
    bool User_serialflag;


public:
    explicit ECGTest_Dialog(QWidget *parent = nullptr);
    ~ECGTest_Dialog();

    void readECGFile(QString FileName);
    void getHistoryData();
    void paintEvent(QPaintEvent *event);
    void drawECGGrid(QPainter &painter,int width,int height,double dots);
    void drawHisECGWave(QPainter &painter,int width,int height,double dots);
    bool serialPortInit();
    void updateECGWave(QPainter &painter,int width,int height,double dots);

private slots:
    void on_btn_quit_clicked();
    void receiveData();


};

#endif // ECGTEST_DIALOG_H
