#include "bloodpressure_dialog.h"
#include "ui_bloodpressure_dialog.h"
#include "user_data.h"
extern User_Data user;

BloodPressure_Dialog::BloodPressure_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BloodPressure_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromUtf8("血压仪"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    QString showText0 = QString("姓名：%1").arg(user.getName());
    ui->lab_name->setText(showText0);
    QString showText1 = QString("年龄：%1").arg(user.getAge());
    ui->lab_age->setText(showText1);

    m_bloodPressure  = new BloodPressure(ui->Plot_Blood,ui->num_HBP,ui->num_LBP,ui->num_PULSE);

    m_bloodPressure->setParm(1,60);
    m_bloodPressure->buildPlot();
    initBP();
}

BloodPressure_Dialog::~BloodPressure_Dialog()
{
    m_bloodPressure->m_serial->serialClose();
    delete m_bloodPressure->m_serial;
    delete ui;
}

// 鼠标移动拖动窗口
void BloodPressure_Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint globalPt = event->globalPosition().toPoint();
        m_offset = globalPt - this->frameGeometry().topLeft();
    }
    QDialog::mousePressEvent(event);
}

void BloodPressure_Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint globalPt = event->globalPosition().toPoint();
        this->move(globalPt - m_offset);
    }
    QDialog::mouseMoveEvent(event);
}
void BloodPressure_Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    QDialog::mouseReleaseEvent(event);
}
void BloodPressure_Dialog::initBP()
{
    int length = 60;
    QVector<unsigned char > HBPHistory;
    HBPHistory.reserve(length);
    QVector<unsigned char > LBPHistory;
    LBPHistory.reserve(length);
    QVector<unsigned char > PulseHistory;
    PulseHistory.reserve(length);

    unsigned char value = 0;
    for(int i=0;i<length;i++)
    {
        value = 120 +rand()%10;
        HBPHistory.append(value);

        value =  80 + rand()%5;
        LBPHistory.append(value);

        value = 65 + rand()%5;
        PulseHistory.append(value);
    }
    m_bloodPressure->drawHistoryData(QDateTime::currentMSecsSinceEpoch(),HBPHistory,LBPHistory,PulseHistory);
    m_bloodPressure->serialPortInit();
}

void BloodPressure_Dialog::on_btn_quit_clicked()
{
    m_bloodPressure->m_serial->serialClose();
    close();
}

