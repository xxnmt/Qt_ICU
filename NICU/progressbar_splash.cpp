#include "progressbar_splash.h"


ProgressBar_Splash::ProgressBar_Splash(int time, QProgressBar *progressbar, QPushButton *btn)
{
    m_progressbar = progressbar;
    m_btn = btn;
    m_elapseTime = time/100;
    m_progressbar->setStyleSheet("QProgressBar{color:rgb(255,255,255);"
                                 "font:12px;text-align:center;}"
                                 "QProgressBar::chunk{background-color:rgb(198,224,237);"
                                 "width:5px;}");
    m_progressbar->setRange(0,100);
    m_progressbar->setValue(0);
    generateNumber();
    m_timer = startTimer(m_elapseTime);
}

void ProgressBar_Splash::generateNumber()
{
    for(int i=1;i<101;i++)m_numList.append(i);
}

void ProgressBar_Splash::updateProgress()
{
    static int num=0;
    m_progressbar->setValue(m_numList[num]);
    num++;
    if(num>=100){
        killTimer(m_timer);
        if(m_btn!=NULL)m_btn->setEnabled(true);
        num=0;
    }

}

void ProgressBar_Splash::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==m_timer) updateProgress();
}
