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
    //this->setWindowFlags(Qt::FramelessWindowHint);

    ui->lab_name->setText(user.getName());
    ui->lab_age->setText(QString::number(user.getAge()));

    m_bloodPressure  = new BloodPressure(ui->Plot_Blood,ui->num_HBP,ui->num_LBP,ui->num_PULSE);

    m_bloodPressure->setParm(1,60);
    m_bloodPressure->buildPlot();
    initBP();
}

BloodPressure_Dialog::~BloodPressure_Dialog()
{
    delete ui;
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

