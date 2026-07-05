#ifndef ECGTEST_DIALOG_H
#define ECGTEST_DIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QList>
#include <QTimer>
#include "serial_tool.h"
#include "heart_data.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class ECGTest_Dialog; }
QT_END_NAMESPACE

class ECGTest_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ECGTest_Dialog(QWidget *parent = nullptr);
    ~ECGTest_Dialog();

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    // 重写鼠标事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void receiveData();
    void on_btn_quit_clicked();
    void updateWaveform();  // 定时刷新

private:
    void readECGFile(QString FileName);
    void getHistoryData();
    void drawInterfaceInfo(QPainter &painter);
    void drawECGGrid(QPainter &painter, int width, int height, double dots);
    void drawHisECGWave(QPainter &painter, int width, int height, double dots,int yOffset);
    void drawRealTimeWave(QPainter &painter, int width, int height, double,int yOffset);
    bool serialPortInit();
    void parseSerialData(const QByteArray &data);

private:
    Ui::ECGTest_Dialog *ui;
    Serial_Tool *User_serial;
    Heart_Data *User_ChannelData[12];
    QJsonArray User_DataArr;
    QList<int> User_newdata;
    bool User_serialflag;
    QTimer *m_updateTimer;
    QPoint m_offset;
};

#endif // ECGTEST_DIALOG_H