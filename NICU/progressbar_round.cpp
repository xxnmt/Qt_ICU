#include "progressbar_round.h"
#include <QPropertyAnimation>
#include "qmath.h"
ProgressBar_Round::ProgressBar_Round(QWidget *parent)
    :QWidget(parent),m_value(0),m_min(0)
{
//双缓冲防黑块(已测试无效)
    setAutoFillBackground(true);
    setAttribute(Qt::WA_OpaquePaintEvent,true);
////////////////////////////////////////////////////
    m_value=0;
    m_min=0;
    m_startAngle=90;
    m_max=100;
    m_outColor = QColor(232,241,240);
    m_inColor = QColor(38,155,175);
    setValue(0);
    m_outBarWidth = 10;
    m_inBarWidth = 8;
}

void ProgressBar_Round::setInColor(const QColor &c)
{
    m_inColor=c;
}

void ProgressBar_Round::setOutColor(const QColor &c)
{
    m_outColor=c;
}

void ProgressBar_Round::setValue(float value) {
    QPropertyAnimation* pa = new QPropertyAnimation(this,"m_value",this);
    pa->setStartValue(m_value);
    pa->setEndValue(value);
    pa->setDuration(2000);
    pa->start();
}

void ProgressBar_Round::paintEvent(QPaintEvent *event)
{

    // 1. 调用父类绘制，清空底层背景
    QWidget::paintEvent(event);

    QPainter painter(this);
    // 2. 抗锯齿，优化绘制边缘
    painter.setRenderHint(QPainter::Antialiasing);
    // 3. 强制填充整个控件区域，清除残留黑块
    painter.fillRect(this->rect(), this->palette().window());
    /////////////////////////已测试无效/////////////////////

    paintOutterBar(painter);
    paintInnerBar(painter);
    paintText(painter);

}

void ProgressBar_Round::resizeEvent(QResizeEvent *event)
{
    int minWidth = qMin(this->width(),this->height());
    m_squarePoint = m_outBarWidth/2;
    m_squareSide = minWidth-m_outBarWidth;
}

void ProgressBar_Round::paintOutterBar(QPainter &p)
{
    QPen pen;
    pen.setWidth(m_outBarWidth);
    pen.setColor(m_outColor);
    p.setPen(pen);
    QRectF rectangle(m_squarePoint,m_squarePoint,m_squareSide,m_squareSide);
    p.drawEllipse(rectangle);
}

void ProgressBar_Round::paintInnerBar(QPainter &p)
{
    QPen pen;
    pen.setWidth(m_inBarWidth);
    pen.setColor(m_inColor);
    p.setPen(pen);
    QRectF rectangle(m_squarePoint,m_squarePoint,m_squareSide,m_squareSide);

    int startAngle = m_startAngle *16;
    int spanAngle = (m_value-m_min)/(m_max-m_min)*360*16*(-1);
    p.drawArc(rectangle,startAngle,spanAngle);
}


void ProgressBar_Round::paintText(QPainter &p)
{
    p.setFont(QFont("微软雅黑",22,75));
    p.setPen(m_inColor);

    p.drawText(m_squarePoint,m_squarePoint,m_squareSide,m_squareSide,Qt::AlignCenter,
               QString::number(m_value/m_max*100,'f',0)+"%");
}

void ProgressBar_Round::setMValue(float value)
{
    m_value=value;
    repaint();
}
float ProgressBar_Round::getMValue(){
    return m_value;

}
