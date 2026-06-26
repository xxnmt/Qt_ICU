#include "progressbar_check.h"
#include <QPainter>

ProgressBar_Check::ProgressBar_Check(QWidget *parent)
{
    setMinimum(0);
    setMaximum(100);
    setValue(0);
}

void ProgressBar_Check::PaintEvent(QPaintEvent*)
{
    QRect rec=QRect(0,0,width()*5/6,height());
    QRect textRec = QRect(width()*5/6,0,width()/6,height());
    const double p=double(value()-minimum())/(maximum()-minimum());
    int x = (int) (rec.width()*p);
    QRect proRec = rec.adjusted(0,0,x-rec.width(),0);

    QPainter painter(this);
    painter.drawPixmap(rec,QPixmap(":/resource_inside/images/progress_back.png"));
    painter.drawPixmap(proRec,QPixmap(":/resource_inside/images/progress_front.png"));

    QString valueStr = QString("%1%").arg(value());
    QFont f = QFont("微软雅黑",10,QFont::Bold);
    painter.setFont(f);
    painter.setPen(QColor("#666666"));
    painter.drawText(textRec,Qt::AlignCenter,valueStr);

}
