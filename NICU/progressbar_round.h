#ifndef PROGRESSBAR_ROUND_H
#define PROGRESSBAR_ROUND_H

#include <QWidget>
#include <QPainter>
class ProgressBar_Round:public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float m_value READ getMValue WRITE setMValue)
public:
    explicit ProgressBar_Round(QWidget *parent=0);
    ~ProgressBar_Round(){}
    void setInColor(const QColor& c);
    void setOutColor(const QColor& c);
    void setValue(float value);
    float getMValue();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    void paintOutterBar(QPainter &p);
    void paintInnerBar(QPainter &p);
    void paintText(QPainter &p);
    void setMValue(float value);

    float m_min;
    float m_max;
    float m_value;
    QColor m_outColor;
    QColor m_inColor;
    float m_squarePoint;
    float m_squareSide;
    int m_startAngle;
    float m_outBarWidth;
    float m_inBarWidth;
};
#endif // PROGRESSBAR_ROUND_H
