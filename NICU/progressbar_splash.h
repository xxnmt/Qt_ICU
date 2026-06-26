#ifndef PROGRESSBAR_SPLASH_H
#define PROGRESSBAR_SPLASH_H
#include <QSplashScreen>
#include <QProgressBar>
#include <QPushButton>
#include <QTimerEvent>
class ProgressBar_Splash: public QSplashScreen
{
    Q_OBJECT
public:
    ProgressBar_Splash(int time,QProgressBar *progressbar, QPushButton *btn);
    ~ProgressBar_Splash(){}
    void generateNumber();
    void updateProgress();
protected:
    void timerEvent(QTimerEvent * event);
private:
    QProgressBar *m_progressbar;
    QList<int> m_numList;
    int m_elapseTime;
    QPushButton *m_btn;
    int m_timer;
};

#endif // PROGRESSBAR_SPLASH_H
