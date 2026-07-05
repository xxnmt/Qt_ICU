#include "ventilator_dialog.h"
#include "ui_ventilator_dialog.h"
#include <QTimer>
#include <QMovie>
#include <QObject>
extern User_Data user;

Ventilator_Dialog::Ventilator_Dialog(QWidget *parent)
    :QDialog(parent),
    ui(new Ui::Ventilator_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("呼吸机"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    QString showText0 = QString("姓名：%1").arg(user.getName());
    ui->lab_name->setText(showText0);
    QString showText1 = QString("年龄：%1").arg(user.getAge());
    ui->lab_age->setText(showText1);
    m_lock = true;
    m_currentMode = VCV;

    showGif();
    serialportInit();
    alarmLight();

    ui->comboBox_ventilationMode->setEnabled(false);
    switchMode(VCV);
}

Ventilator_Dialog::~Ventilator_Dialog()
{
    m_serial->serialClose();
    delete ui;
}

// 鼠标移动拖动窗口
void Ventilator_Dialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint globalPt = event->globalPosition().toPoint();
        m_offset = globalPt - this->frameGeometry().topLeft();
    }
    QDialog::mousePressEvent(event);
}

void Ventilator_Dialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint globalPt = event->globalPosition().toPoint();
        this->move(globalPt - m_offset);
    }
    QDialog::mouseMoveEvent(event);
}
void Ventilator_Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    QDialog::mouseReleaseEvent(event);
}

void Ventilator_Dialog::showGif()
{
    QMovie *movie=new QMovie(":/resource_inside/images/breathgif.gif");
    ui->lab_Gif->setMovie(movie);
    ui->lab_Gif->setScaledContents(true);
    movie->start();
}

bool Ventilator_Dialog::serialportInit()
{
    m_serial =new Serial_Tool;
    m_serial->m_serialport=new QSerialPort();
    connect(m_serial->m_serialport,SIGNAL(readyRead()),this,SLOT(receiveData()));
    m_serial->serialOpen("com4");
    return true;
}

void Ventilator_Dialog::alarmLight()
{
    ui->widget_light->setBackgroundColor(QColor(23,186,154));
    m_lightState = 0;
    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer,SIGNAL(timeout()),this, SLOT(updateLight()));
    m_timer->start();
}

void Ventilator_Dialog::on_btn_lock_clicked()
{
    m_lock = !m_lock;

    if(!m_lock){
        ui->btn_lock->setStyleSheet(
            "QPushButton {"
            "    border-image: url(:/resource_inside/images/unlock.png);"
            "    border: none;"
            "}"
            );
        ui->comboBox_ventilationMode->setEnabled(true);
        m_serial->m_serialport->write("VENT_STOP");
    }
    else{
        ui->btn_lock->setStyleSheet(
            "QPushButton {"
            "    border-image: url(:/resource_inside/images/lock.png);"
            "    border: none;"
            "}"
            );
        ui->comboBox_ventilationMode->setEnabled(false);
        sendSetParams();
    }

    switchMode(m_currentMode);
}

void Ventilator_Dialog::on_btn_quit_clicked()
{
    m_timer->stop();
    m_serial->serialClose();
    close();
}

void Ventilator_Dialog::updateLight()
{
    if(m_lightState==0)
    {
        ui->widget_light->setGreenLight();
        m_lightState =1;
    }
    else if(m_lightState ==1)
    {
        ui->widget_light->setYellowLight();
        m_lightState=0;
    }
    else if(m_lightState == 2)
    {
        ui->widget_light->setRedLight();
        m_lightState =3;
    }
    else if(m_lightState ==3)
    {
        ui->widget_light->setOrangeLight();
        m_lightState =2;
    }
}

void Ventilator_Dialog::receiveData()
{
    QByteArray data = m_serial->m_serialport->readAll();
    QString strData = QString::fromLocal8Bit(data);

    if(strData.startsWith("VENT_DATA:")) {
        QStringList parts = strData.split(':');
        if (parts.size() >= 12) {
            ui->doubleSpinBox_leakageVolume->setValue(parts[3].toDouble());
            ui->doubleSpinBox_minuteVentilation->setValue(parts[4].toDouble());
            ui->doubleSpinBox_ieRatio->setValue(parts[11].toDouble());

            if (m_currentMode == VCV) {
                ui->doubleSpinBox_inspiratoryPressure->setValue(parts[8].toDouble());
            } else if (m_currentMode == PCV) {
                ui->doubleSpinBox_tidalVolume->setValue(parts[2].toDouble());
            } else if (m_currentMode == PSV) {
                ui->doubleSpinBox_tidalVolume->setValue(parts[2].toDouble());
                ui->spinBox_respiratoryRate->setValue(parts[5].toInt());
                ui->doubleSpinBox_inspiratoryTime->setValue(parts[6].toDouble());
            }
        }
    }
    else if(strData.startsWith("e")) {
        m_lightState=2;
    }
}

void Ventilator_Dialog::on_comboBox_ventilationMode_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        m_currentMode = VCV;
        break;
    case 1:
        m_currentMode = PCV;
        break;
    case 2:
        m_currentMode = PSV;
        break;
    }
    switchMode(m_currentMode);
}

void Ventilator_Dialog::switchMode(VentilationMode mode)
{
    updateParamStatus("tidalVolume", getParamType(mode, "tidalVolume"));
    updateParamStatus("leakageVolume", getParamType(mode, "leakageVolume"));
    updateParamStatus("minuteVentilation", getParamType(mode, "minuteVentilation"));
    updateParamStatus("respiratoryRate", getParamType(mode, "respiratoryRate"));
    updateParamStatus("inspiratoryTime", getParamType(mode, "inspiratoryTime"));
    updateParamStatus("riseTime", getParamType(mode, "riseTime"));
    updateParamStatus("inspiratoryPressure", getParamType(mode, "inspiratoryPressure"));
    updateParamStatus("expiratoryPressure", getParamType(mode, "expiratoryPressure"));
    updateParamStatus("backupRate", getParamType(mode, "backupRate"));
    updateParamStatus("ieRatio", getParamType(mode, "ieRatio"));
}

ParamType Ventilator_Dialog::getParamType(VentilationMode mode, const QString& paramName)
{
    if (paramName == "expiratoryPressure" || paramName == "backupRate") {
        return SET_PARAM;
    }

    if (mode == VCV) {
        if (paramName == "tidalVolume" || paramName == "respiratoryRate" || paramName == "inspiratoryTime") {
            return SET_PARAM;
        } else if (paramName == "riseTime") {
            return NA_PARAM;
        } else if (paramName == "minuteVentilation" || paramName == "ieRatio") {
            return DERIVED_PARAM;
        } else {
            return MONITOR_PARAM;
        }
    } else if (mode == PCV) {
        if (paramName == "respiratoryRate" || paramName == "inspiratoryTime" ||
            paramName == "riseTime" || paramName == "inspiratoryPressure") {
            return SET_PARAM;
        } else if (paramName == "minuteVentilation" || paramName == "ieRatio") {
            return DERIVED_PARAM;
        } else {
            return MONITOR_PARAM;
        }
    } else if (mode == PSV) {
        if (paramName == "riseTime" || paramName == "inspiratoryPressure") {
            return SET_PARAM;
        } else if (paramName == "minuteVentilation" || paramName == "ieRatio" || paramName == "inspiratoryTime") {
            return DERIVED_PARAM;
        } else {
            return MONITOR_PARAM;
        }
    }

    return MONITOR_PARAM;
}

void Ventilator_Dialog::updateParamStatus(const QString& paramName, ParamType type)
{
    QWidget* widget = nullptr;

    if (paramName == "tidalVolume") widget = ui->doubleSpinBox_tidalVolume;
    else if (paramName == "leakageVolume") widget = ui->doubleSpinBox_leakageVolume;
    else if (paramName == "minuteVentilation") widget = ui->doubleSpinBox_minuteVentilation;
    else if (paramName == "respiratoryRate") widget = ui->spinBox_respiratoryRate;
    else if (paramName == "inspiratoryTime") widget = ui->doubleSpinBox_inspiratoryTime;
    else if (paramName == "riseTime") widget = ui->doubleSpinBox_riseTime;
    else if (paramName == "inspiratoryPressure") widget = ui->doubleSpinBox_inspiratoryPressure;
    else if (paramName == "expiratoryPressure") widget = ui->doubleSpinBox_expiratoryPressure;
    else if (paramName == "backupRate") widget = ui->spinBox_backupRate;
    else if (paramName == "ieRatio") widget = ui->doubleSpinBox_ieRatio;

    if (!widget) return;

    switch (type) {
    case SET_PARAM:
        widget->setEnabled(!m_lock);
        widget->setVisible(true);
        break;
    case MONITOR_PARAM:
    case DERIVED_PARAM:
        widget->setEnabled(false);
        widget->setVisible(true);
        break;
    case NA_PARAM:
        widget->setVisible(false);
        break;
    }
}

void Ventilator_Dialog::sendSetParams()
{
    QString modeStr;
    double tidalVol = 0, inspPressure = 0, riseTime = 0;
    int respRate = 0;
    double inspTime = 0;

    switch(m_currentMode) {
    case VCV:
        modeStr = "VCV";
        tidalVol = ui->doubleSpinBox_tidalVolume->value();
        respRate = ui->spinBox_respiratoryRate->value();
        inspTime = ui->doubleSpinBox_inspiratoryTime->value();
        break;
    case PCV:
        modeStr = "PCV";
        inspPressure = ui->doubleSpinBox_inspiratoryPressure->value();
        respRate = ui->spinBox_respiratoryRate->value();
        inspTime = ui->doubleSpinBox_inspiratoryTime->value();
        riseTime = ui->doubleSpinBox_riseTime->value();
        break;
    case PSV:
        modeStr = "PSV";
        inspPressure = ui->doubleSpinBox_inspiratoryPressure->value();
        riseTime = ui->doubleSpinBox_riseTime->value();
        break;
    }

    double expPressure = ui->doubleSpinBox_expiratoryPressure->value();
    int backupRate = ui->spinBox_backupRate->value();

    QString msg = QString("VENT_SET:%1:%2:%3:%4:%5:%6:%7:%8")
            .arg(modeStr)
            .arg(QString::number(tidalVol))
            .arg(QString::number(respRate))
            .arg(QString::number(inspTime))
            .arg(QString::number(riseTime))
            .arg(QString::number(inspPressure))
            .arg(QString::number(expPressure))
            .arg(QString::number(backupRate));

    m_serial->m_serialport->write(msg.toUtf8());
}
