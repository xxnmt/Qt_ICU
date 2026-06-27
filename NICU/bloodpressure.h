#ifndef BLOODPRESSURE_H
#define BLOODPRESSURE_H
#include <QObject>
#include <QLabel>
#include <QElapsedTimer>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QLCDNumber>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>
#include <qwt_text.h>
#include "plot_data.h"
#include "serial_tool.h"
#include <QObject>
#include <QtQwt/qwt.h>
class BloodPressure : public QObject
{
    Q_OBJECT
public:
    explicit BloodPressure(QObject *parent = nullptr);
    BloodPressure (QwtPlot*plot,QLCDNumber*hbp,QLCDNumber*lbp,QLCDNumber*pulse);
    void setParm(int sampleRate,double xWidth);
    void initPlot();
    void buildPlot();
    void drawHistoryData(quint64 ulStartTime, QVector<unsigned char>vctHBP,QVector<unsigned char>vctLBP,  QVector<unsigned char>vctPulse);
    void addPlotGrid();
    void addLegend();
    void addManifier();
    void addPanner();
    void addCurve();
    void serialPortInit();

    Serial_Tool *m_serial;

private slots:
    void receiveData();
protected:
    void updateCurve(QByteArray message);

private:
    class TestData{
    public:
        QwtPlotMagnifier *pManifier;
        QwtPlotCurve *pHBPCurve;
        Plot_Data *pHBPData;
        QwtPlotCurve *pLBPCurve;
        Plot_Data *pLBPData;
        QwtPlotCurve *pPulseCurve;
        Plot_Data *pPulseData;

        QwtPanner *pPanner;
        QwtInterval interval;
        QElapsedTimer eTimer;

    };
    QwtPlot *m_BPPlot;
    TestData *m_testData;

    QLCDNumber *m_hbp;
    QLCDNumber *m_lbp;
    QLCDNumber *m_Pulse;
};

// 这段代码定义了一个继承自 QwtScaleDraw 的自定义类 TimeScaleDraw，用于在 Qwt 绘图中自定义坐标轴标签的显示格式。
// 功能
// 将坐标轴上的数值（毫秒级时间戳）转换为可读的日期时间字符串
// 示格式为：
// 第一行：hh:mm:ss（时:分:秒）
// 第二行：yy-MM-dd（年-月-日）
class TimeScaleDraw:public QwtScaleDraw
{
public:
    virtual QwtText label(double v)const
    {
        QDateTime time = QDateTime::fromMSecsSinceEpoch(v);
        return time.toString("hh:mm::ss\nyy-MM-dd");
    }
};
#endif // BLOODPRESSURE_H
