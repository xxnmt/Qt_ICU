#include "plot_data.h"

Plot_Data::Plot_Data() {}

size_t Plot_Data::size() const
{
    return m_value.size();
}

QPointF Plot_Data::sample(size_t i) const
{
    return m_value[i];
}

QRectF Plot_Data::boundingRect() const
{
    return m_boundingRect;
}

void Plot_Data::setParam(int sampleRate, double xWidth)
{
    m_sampleRate = sampleRate;
    m_xWidth = xWidth;
    m_intervalTime = 1000;
    m_intergrationTime = m_intervalTime;
    m_maxCount = m_sampleRate * m_xWidth+1;
    m_listPendingValue.clear();
}

void Plot_Data::addBaseData(quint64 startTime, QVector<unsigned char> basedata)
{
    int iC=basedata.count();
    m_value.resize(iC);
    m_intergrationTime+=startTime;
    for(int i=0;i<iC;i++){
        m_value[i]=QPointF(m_intergrationTime,basedata[i]);
        m_intergrationTime+=m_intervalTime;

    }

}

bool Plot_Data::updateCurveData(unsigned char recvdata)
{
    QPointF point(0,0);
    point.setX(m_intergrationTime);
    point.setY(recvdata);
    int iCount = m_value.size();
    if(iCount < m_maxCount)
        m_value.append(point);
    else
    {
        int idx = 0;
        for(idx=0;idx<iCount-1;idx++)
        {
            m_value[idx]=m_value[idx+1];
        }
        m_value[idx] = point;
    }
    m_intergrationTime += m_intervalTime;
    return true;

}

QwtInterval Plot_Data::getXInterval()
{
    return QwtInterval(m_value.first().x(),m_value.last().x());
}


