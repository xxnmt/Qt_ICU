#include "bloodpressure.h"

BloodPressure::BloodPressure(QObject *parent)
    : QObject{parent}
{}

BloodPressure::BloodPressure(QwtPlot *plot, QLCDNumber *hbp, QLCDNumber *lbp, QLCDNumber *pulse)
{
    m_BPPlot=plot;
    m_hbp=hbp;
    m_lbp=lbp;
    m_Pulse=pulse;

    m_testData=new TestData();
    m_testData->pHBPData=new Plot_Data;
    m_testData->pLBPData=new Plot_Data;
    m_testData->pPulseData=new Plot_Data;

    m_serial=new Serial_Tool;

}

void BloodPressure::setParm(int sampleRate, double xWidth)
{
    m_testData->pHBPData->setParam(sampleRate,xWidth);
    m_testData->pLBPData->setParam(sampleRate,xWidth);
    m_testData->pPulseData->setParam(sampleRate,xWidth);
}

void BloodPressure::initPlot()
{
    m_BPPlot->setAxisScaleDraw(QwtPlot::xBottom,new TimeScaleDraw());
    m_BPPlot->setAxisScale(QwtPlot::yLeft,0,160);
    m_BPPlot->setAxisScale(QwtPlot::xBottom,m_testData->interval.minValue(),m_testData->interval.maxValue());
}
void BloodPressure::buildPlot(){
    initPlot();
    addPlotGrid();
    addLegend();
    addManifier();
    addPanner();
    addCurve();
}
void BloodPressure::addPlotGrid()
{
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(Qt::gray,0.0, Qt::DotLine);
    grid->enableY(true);
    grid->enableYMin(true);
    grid->enableX(true);
    grid->enableXMin(true);
    grid->attach(m_BPPlot);

}
void BloodPressure::addLegend()
{
    m_BPPlot->insertLegend(new QwtLegend(),QwtPlot::RightLegend);
}
void BloodPressure::addManifier()
{
    m_testData->pManifier = new QwtPlotMagnifier(m_BPPlot->canvas());
    m_testData->pManifier->setAxisEnabled(QwtPlot::yLeft,false);
}
void BloodPressure::addPanner()
{
    m_testData->pPanner = new QwtPlotPanner(m_BPPlot->canvas());
    m_testData->pPanner->setOrientations(Qt::Horizontal);
}

void BloodPressure::drawHistoryData(quint64 ulStartTime, QVector<unsigned char>vctHBP,QVector<unsigned char>vctLBP,  QVector<unsigned char>vctPulse)
{
    m_testData->pHBPData->addBaseData(ulStartTime,vctHBP);
    m_testData->pLBPData->addBaseData(ulStartTime,vctLBP);
    m_testData->pPulseData->addBaseData(ulStartTime,vctPulse);

    QwtInterval interval = m_testData->pHBPData->getXInterval();
    m_testData->interval = interval;
    m_BPPlot->setAxisScale(QwtPlot::xBottom,m_testData->interval.minValue(),m_testData->interval.maxValue());
    m_BPPlot->replot();
}
void BloodPressure::addCurve()
{
    m_testData->pLBPCurve = new QwtPlotCurve("LBP");
    m_testData->pLBPCurve->setStyle(QwtPlotCurve::Lines);
    m_testData->pLBPCurve->setPen(QColor("#6abf31"),3);
    m_testData->pLBPCurve->setData(m_testData->pLBPData);

    m_testData->pHBPCurve = new QwtPlotCurve("HBP");
    m_testData->pHBPCurve->setStyle(QwtPlotCurve::Lines);
    m_testData->pHBPCurve->setPen(QColor("#F40200"),3);
    m_testData->pHBPCurve->setData(m_testData->pHBPData);

    m_testData->pPulseCurve = new QwtPlotCurve("Pulse");
    m_testData->pPulseCurve->setStyle(QwtPlotCurve::Lines);
    m_testData->pPulseCurve->setPen(QColor("#EEFF66"),3);
    m_testData->pPulseCurve->setData(m_testData->pPulseData);

    m_testData->pHBPCurve->attach(m_BPPlot);
    m_testData->pLBPCurve->attach(m_BPPlot);
    m_testData->pPulseCurve->attach(m_BPPlot);
}

void BloodPressure::serialPortInit(){
    m_serial->m_serialport = new QSerialPort();
    connect(m_serial->m_serialport,SIGNAL(readyRead()),this,SLOT(receiveData()));
    m_serial->serialOpen("com3");
}
void BloodPressure::receiveData(){
    QByteArray message;
    message.append(m_serial->m_serialport->readAll());
    updateCurve(message);
}
void BloodPressure::updateCurve(QByteArray message){
    m_testData->pHBPData->updateCurveData(message.at(0));
    m_testData->pLBPData->updateCurveData(message.at(1));
    m_testData->pPulseData->updateCurveData(message.at(2));

    m_testData->interval = m_testData->pHBPData->getXInterval();

    m_BPPlot->setAxisScale(QwtPlot::xBottom,m_testData->interval.minValue(),m_testData->interval.maxValue());

    m_BPPlot->updateAxes();

    unsigned char num = message.at(0);
    m_hbp->display(num);
    num = message.at(1);
    m_lbp->display(num);
    num = message.at(2);
    m_Pulse->display(num);
    m_BPPlot->replot();
}

