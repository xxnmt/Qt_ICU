#ifndef PROGRESSBAR_CHECK_H
#define PROGRESSBAR_CHECK_H
#include <QWidget>
#include <QProgressBar>
class ProgressBar_Check:public QProgressBar
{
public:
    ProgressBar_Check(QWidget *parent = 0);
protected:
    void PaintEvent(QPaintEvent*);
};

#endif // PROGRESSBAR_CHECK_H
