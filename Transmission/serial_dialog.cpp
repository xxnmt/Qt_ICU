#include "serial_dialog.h"
#include "ui_serial_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

// 心跳波形数据
int arrs[]={16,12,9,8,6,34,20,22,20,16,12,9,8,9,
              10,8,6,-1,2,-3,-7,-8 ,-7,-6,7,2,-1,1,
              9,9,10,8,6,-1,2,-3,-7,-8,-7,-6,-6,7,2,
              -1,1,9,-7,-8,-7,-6,7,2,-1,1,-1,2,-3,-7,
              -8 ,8,6,-7,2,-1,1,9,-101,-200,-120,-40,
              40,120,280,459,670,835,900,835,670,450,
              340,240,27,18,14,10,6};
const int LENGTH = sizeof(arrs)/sizeof(int);

// ==================== 构造函数/析构函数 ====================

Serial_Dialog::Serial_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serial_Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("数据传输客户端"));

    // 初始化各通道
    initChannels();

    // 刷新所有ComboBox
    refreshAllComboBoxes();
}

Serial_Dialog::~Serial_Dialog()
{
    // 关闭所有串口
    for (auto it = m_serialPorts.begin(); it != m_serialPorts.end(); ++it) {
        if (it.value()->isOpen()) {
            it.value()->close();
        }
        delete it.value();
    }
    m_serialPorts.clear();
    delete ui;
}

// ==================== 初始化函数 ====================

void Serial_Dialog::initChannels()
{
    // 心跳通道
    m_heartChannel.functionName = "心跳";
    m_heartChannel.comboBox = ui->comboBox_heart;
    m_heartChannel.connectBtn = ui->btn_connect_heart;
    m_heartChannel.transmitBtn = ui->btn_heart;
    m_heartChannel.statusLabel = ui->lab_status_heartCOM;

    // 血压通道
    m_pressureChannel.functionName = "血压";
    m_pressureChannel.comboBox = ui->comboBox_bloodPressure;
    m_pressureChannel.connectBtn = ui->btn_connect_bloodPressure;
    m_pressureChannel.transmitBtn = ui->btn_bloodPressure;
    m_pressureChannel.statusLabel = ui->lab_status_bloodpressure;

    // 呼吸通道
    m_breathChannel.functionName = "呼吸";
    m_breathChannel.comboBox = ui->comboBox_breath;
    m_breathChannel.connectBtn = ui->btn_connect_breath;
    m_breathChannel.transmitBtn = ui->btn_breath;
    m_breathChannel.statusLabel = ui->lab_status_breath;

    // 紧急通道
    m_hurryChannel.functionName = "紧急";
    m_hurryChannel.comboBox = ui->comboBox_hurry;
    m_hurryChannel.connectBtn = ui->btn_connect_hurry;
    m_hurryChannel.transmitBtn = ui->btn_hurry;
    m_hurryChannel.statusLabel = ui->lab_status_hurry;

    // HDD通道（血透仪）
    m_hddChannel.functionName = "血透";
    m_hddChannel.comboBox = ui->comboBox_connect_HDD;
    m_hddChannel.connectBtn = ui->btn_HDD;
    m_hddChannel.transmitBtn = ui->btn_HDD_2;
    m_hddChannel.statusLabel = ui->lab_staus_HDD;

    // 设置初始UI状态
    setChannelConnected(m_heartChannel, false);
    setChannelConnected(m_pressureChannel, false);
    setChannelConnected(m_breathChannel, false);
    setChannelConnected(m_hurryChannel, false);
    setChannelConnected(m_hddChannel, false);
}

void Serial_Dialog::refreshAllComboBoxes()
{
    updateComboBoxList(ui->comboBox_heart);
    updateComboBoxList(ui->comboBox_bloodPressure);
    updateComboBoxList(ui->comboBox_breath);
    updateComboBoxList(ui->comboBox_hurry);
    updateComboBoxList(ui->comboBox_connect_HDD);
}

void Serial_Dialog::updateComboBoxList(QComboBox* comboBox)
{
    if (!comboBox) return;

    QString currentText = comboBox->currentText();
    comboBox->blockSignals(true);
    comboBox->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo& port : ports) {
        comboBox->addItem(port.portName(), port.portName());
    }

    int index = comboBox->findText(currentText);
    if (index >= 0) {
        comboBox->setCurrentIndex(index);
    }
    comboBox->blockSignals(false);
}

// ==================== 串口管理函数 ====================

bool Serial_Dialog::isPortAvailable(const QString& portName)
{
    if (m_serialPorts.contains(portName)) {
        if (m_portRefCount.contains(portName) && m_portRefCount[portName] > 0) {
            return false;
        }
    }
    return true;
}

QSerialPort* Serial_Dialog::getSerialPort(const QString& portName)
{
    if (m_serialPorts.contains(portName)) {
        return m_serialPorts[portName];
    }
    return nullptr;
}

bool Serial_Dialog::openSerialPortForChannel(const QString& portName, FunctionChannel& channel)
{
    bool allowShare = false;
    if (&channel == &m_breathChannel || &channel == &m_hurryChannel || &channel == &m_hddChannel) {
        allowShare = true;
    }

    if (m_serialPorts.contains(portName) && m_portRefCount.contains(portName) && m_portRefCount[portName] > 0) {
        if (!allowShare) {
            QMessageBox::warning(this, "错误",
                                 QString("串口 %1 已被其他功能占用！").arg(portName));
            return false;
        } else {
            if (m_heartChannel.isConnected && m_heartChannel.selectedPort == portName) {
                QMessageBox::warning(this, "错误",
                                     QString("串口 %1 已被心跳功能占用，呼吸/紧急/血透不能共享！").arg(portName));
                return false;
            }
            if (m_pressureChannel.isConnected && m_pressureChannel.selectedPort == portName) {
                QMessageBox::warning(this, "错误",
                                     QString("串口 %1 已被血压功能占用，呼吸/紧急/血透不能共享！").arg(portName));
                return false;
            }
        }
    }

    QSerialPort* serial = nullptr;

    if (!m_serialPorts.contains(portName)) {
        serial = new QSerialPort(portName, this);
        serial->setBaudRate(QSerialPort::Baud115200);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if (!serial->open(QIODevice::ReadWrite)) {
            QMessageBox::critical(this, "错误",
                                  QString("无法打开串口 %1: %2")
                                      .arg(portName)
                                      .arg(serial->errorString()));
            delete serial;
            return false;
        }

        m_serialPorts[portName] = serial;
        m_portRefCount[portName] = 1;

        connect(serial, &QSerialPort::readyRead, [this, portName]() {
            QSerialPort* s = getSerialPort(portName);
            if (s) {
                QByteArray data = s->readAll();
                qDebug() << "Received from" << portName << ":" << data;

                QString strData = QString::fromLocal8Bit(data);
                if (strData.startsWith("HDD:")) {
                    QString command = strData.mid(4);
                    if (m_hddChannel.isConnected && m_hddChannel.selectedPort == portName) {
                        m_hddChannel.currentCommand = command;
                        setChannelTransmitting(m_hddChannel, true);
                        startChannelTimer(m_hddChannel);
                    }
                } else if (strData.startsWith("VENT_SET:")) {
                    QStringList parts = strData.split(':');
                    if (parts.size() >= 9 && m_breathChannel.isConnected && m_breathChannel.selectedPort == portName) {
                        m_breathChannel.currentVentMode = parts[1];
                        m_breathChannel.tidalVolume = parts[2].toDouble();
                        m_breathChannel.respiratoryRate = parts[3].toInt();
                        m_breathChannel.inspiratoryTime = parts[4].toDouble();
                        m_breathChannel.riseTime = parts[5].toDouble();
                        m_breathChannel.inspiratoryPressure = parts[6].toDouble();
                        m_breathChannel.expiratoryPressure = parts[7].toDouble();
                        m_breathChannel.backupRate = parts[8].toInt();

                        if (m_breathChannel.isTransmitting) {
                            stopChannelTimer(m_breathChannel);
                        }

                        setChannelTransmitting(m_breathChannel, true);
                        startChannelTimer(m_breathChannel);

                        qDebug() << "Ventilator parameters updated, mode:" << m_breathChannel.currentVentMode;
                    }
                } else if (strData.startsWith("VENT_STOP")) {
                    if (m_breathChannel.isConnected && m_breathChannel.selectedPort == portName) {
                        setChannelTransmitting(m_breathChannel, false);
                        stopChannelTimer(m_breathChannel);
                        qDebug() << "Ventilator stopped";
                    }
                }
            }
        });

        qDebug() << "串口" << portName << "已打开";
    } else {
        m_portRefCount[portName] = m_portRefCount[portName] + 1;
        serial = m_serialPorts[portName];
        qDebug() << "串口" << portName << "引用计数:" << m_portRefCount[portName];
    }

    channel.selectedPort = portName;
    setChannelConnected(channel, true);

    return true;
}

void Serial_Dialog::closeSerialPortForChannel(FunctionChannel& channel)
{
    if (!channel.isConnected || channel.selectedPort.isEmpty()) {
        return;
    }

    QString portName = channel.selectedPort;

    if (channel.isTransmitting) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
    }

    if (m_portRefCount.contains(portName)) {
        m_portRefCount[portName] = m_portRefCount[portName] - 1;
        qDebug() << "串口" << portName << "引用计数:" << m_portRefCount[portName];

        if (m_portRefCount[portName] <= 0) {
            m_portRefCount.remove(portName);

            if (m_serialPorts.contains(portName)) {
                QSerialPort* serial = m_serialPorts[portName];
                if (serial->isOpen()) {
                    serial->clear();
                    serial->close();
                }
                delete serial;
                m_serialPorts.remove(portName);
                qDebug() << "串口" << portName << "已关闭";
            }
        }
    }

    channel.selectedPort.clear();
    setChannelConnected(channel, false);
}

// ==================== 通道状态管理 ====================

void Serial_Dialog::setChannelConnected(FunctionChannel& channel, bool connected)
{
    channel.isConnected = connected;

    if (connected) {
        if (channel.statusLabel) {
            channel.statusLabel->setStyleSheet("background-color:rgb(0,255,0);border-radius:12px;");
        }
        channel.connectBtn->setText(QString::fromUtf8("断开"));
        channel.comboBox->setEnabled(false);
        channel.transmitBtn->setEnabled(true);
        channel.transmitBtn->setStyleSheet("background-color:rgb(255,0,0);");
        channel.transmitBtn->setText(getTransmitButtonText(channel));
    } else {
        if (channel.statusLabel) {
            channel.statusLabel->setStyleSheet("background-color:rgb(255,0,0);border-radius:12px;");
        }
        channel.connectBtn->setText(QString::fromUtf8("连接"));
        channel.comboBox->setEnabled(true);
        channel.transmitBtn->setEnabled(false);
        channel.transmitBtn->setStyleSheet("background-color:rgb(255,0,0);");
        channel.transmitBtn->setText(getTransmitButtonText(channel));
    }
}

void Serial_Dialog::setChannelTransmitting(FunctionChannel& channel, bool transmitting)
{
    channel.isTransmitting = transmitting;

    if (transmitting) {
        channel.transmitBtn->setStyleSheet("background-color:rgb(0,255,0);");
        channel.transmitBtn->setText(QString::fromUtf8("停止") + channel.functionName);
    } else {
        channel.transmitBtn->setStyleSheet("background-color:rgb(255,0,0);");
        channel.transmitBtn->setText(QString::fromUtf8("开始") + channel.functionName);
    }
}

// 【修正】实现 getTransmitButtonText 函数
QString Serial_Dialog::getTransmitButtonText(const FunctionChannel& channel) const
{
    return QString::fromUtf8("开始") + channel.functionName;
}

void Serial_Dialog::updateChannelUI(FunctionChannel& channel)
{
    Q_UNUSED(channel);
}

// ==================== 定时器管理 ====================

void Serial_Dialog::startChannelTimer(FunctionChannel& channel)
{
    if (channel.timerId != 0) {
        return;
    }

    int interval = 0;
    if (&channel == &m_heartChannel) {
        interval = 200;
    } else if (&channel == &m_pressureChannel) {
        interval = 1000;
    } else if (&channel == &m_breathChannel) {
        interval = 1000;
    } else if (&channel == &m_hurryChannel) {
        interval = 500;
    } else if (&channel == &m_hddChannel) {
        interval = 100;
    }

    if (interval > 0) {
        channel.timerId = startTimer(interval);
        qDebug() << channel.functionName << "定时器启动，间隔:" << interval << "ms";
    }
}

void Serial_Dialog::stopChannelTimer(FunctionChannel& channel)
{
    if (channel.timerId != 0) {
        killTimer(channel.timerId);
        channel.timerId = 0;
        qDebug() << channel.functionName << "定时器停止";
    }
}

void Serial_Dialog::timerEvent(QTimerEvent* event)
{
    if (m_heartChannel.isTransmitting && event->timerId() == m_heartChannel.timerId) {
        sendHeartData(m_heartChannel);
        return;
    }

    if (m_pressureChannel.isTransmitting && event->timerId() == m_pressureChannel.timerId) {
        sendPressureData(m_pressureChannel);
        return;
    }

    if (m_breathChannel.isTransmitting && event->timerId() == m_breathChannel.timerId) {
        sendBreathData(m_breathChannel);
        return;
    }

    if (m_hurryChannel.isTransmitting && event->timerId() == m_hurryChannel.timerId) {
        sendHurryData(m_hurryChannel);
        return;
    }

    if (m_hddChannel.isTransmitting && event->timerId() == m_hddChannel.timerId) {
        sendHddData(m_hddChannel);
        return;
    }
}

// ==================== 数据发送函数 ====================

void Serial_Dialog::sendHeartData(FunctionChannel& channel)
{
    QSerialPort* serial = getSerialPort(channel.selectedPort);
    if (!serial || !serial->isOpen()) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        return;
    }

    QByteArray msg;
    QString strnums;
    int nums[12];

    for(int i = 0; i < 12; i++) {
        nums[i] = arrs[channel.dataIndex] + (unsigned)rand() % 7;
        strnums.append(QString::number(nums[i]) + ",");
    }

    channel.dataIndex++;
    if(channel.dataIndex >= LENGTH) {
        channel.dataIndex = 0;
    }

    msg.append(strnums.toUtf8());
    serial->write(msg);

    qDebug() << "Heart data sent to" << channel.selectedPort;
}

void Serial_Dialog::sendPressureData(FunctionChannel& channel)
{
    QSerialPort* serial = getSerialPort(channel.selectedPort);
    if (!serial || !serial->isOpen()) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        return;
    }

    QByteArray message;
    unsigned char hp = (unsigned char)(120 + rand() % 10);
    unsigned char lp = (unsigned char)(80 + rand() % 5);
    unsigned char pulse = (unsigned char)(65 + rand() % 5);

    message.append(hp);
    message.append(lp);
    message.append(pulse);
    serial->write(message);

    qDebug() << "Pressure data sent to" << channel.selectedPort;
}

void Serial_Dialog::sendBreathData(FunctionChannel& channel)
{
    QSerialPort* serial = getSerialPort(channel.selectedPort);
    if (!serial || !serial->isOpen()) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        return;
    }

    QString mode = channel.currentVentMode;
    double tidalVol = 0;
    int respRate = 0;
    double inspTime = 0;
    double riseTime = 0;
    double inspPressure = 0;
    double expPressure = channel.expiratoryPressure;
    int backupRate = channel.backupRate;

    double leak = 0;
    double minuteVol = 0;
    double ieRatio = 0;

    if (mode == "VCV") {
        tidalVol = channel.tidalVolume;
        respRate = channel.respiratoryRate;
        inspTime = channel.inspiratoryTime;
        riseTime = 0;
        inspPressure = 16 + (rand() % 7 - 3);
        leak = 20 + (rand() % 9 - 4);
        minuteVol = tidalVol * respRate / 1000;
        double cycleTime = 60.0 / respRate;
        ieRatio = inspTime / (cycleTime - inspTime);
    } else if (mode == "PCV") {
        inspPressure = channel.inspiratoryPressure;
        respRate = channel.respiratoryRate;
        inspTime = channel.inspiratoryTime;
        riseTime = channel.riseTime;
        tidalVol = 500 + (rand() % 21 - 10);
        leak = 20 + (rand() % 9 - 4);
        minuteVol = tidalVol * respRate / 1000;
        double cycleTime = 60.0 / respRate;
        ieRatio = inspTime / (cycleTime - inspTime);
    } else if (mode == "PSV") {
        inspPressure = channel.inspiratoryPressure;
        riseTime = channel.riseTime;
        tidalVol = 500 + (rand() % 21 - 10);
        respRate = 13 + rand() % 8;
        inspTime = 0.6 + (rand() % 13) * 0.1;
        leak = 20 + (rand() % 9 - 4);
        minuteVol = tidalVol * respRate / 1000;
        double cycleTime = 60.0 / respRate;
        ieRatio = inspTime / (cycleTime - inspTime);
    }

    QString msg = QString("VENT_DATA:%1:%2:%3:%4:%5:%6:%7:%8:%9:%10:%11")
            .arg(mode)
            .arg(QString::number(tidalVol, 'f', 1))
            .arg(QString::number(leak, 'f', 1))
            .arg(QString::number(minuteVol, 'f', 1))
            .arg(QString::number(respRate))
            .arg(QString::number(inspTime, 'f', 2))
            .arg(QString::number(riseTime, 'f', 1))
            .arg(QString::number(inspPressure, 'f', 1))
            .arg(QString::number(expPressure, 'f', 1))
            .arg(QString::number(backupRate))
            .arg(QString::number(ieRatio, 'f', 2));

    serial->write(msg.toUtf8());
    qDebug() << "Breath data sent to" << channel.selectedPort << ":" << msg;
}

void Serial_Dialog::sendHurryData(FunctionChannel& channel)
{
    QSerialPort* serial = getSerialPort(channel.selectedPort);
    if (!serial || !serial->isOpen()) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        return;
    }

    serial->write("e");
    qDebug() << "Emergency signal sent to" << channel.selectedPort;

    setChannelTransmitting(channel, false);
    stopChannelTimer(channel);
    QMessageBox::information(this, "提示",
                             QString("紧急信号已发送到串口 %1").arg(channel.selectedPort));
}

void Serial_Dialog::sendHddData(FunctionChannel& channel)
{
    QSerialPort* serial = getSerialPort(channel.selectedPort);
    if (!serial || !serial->isOpen()) {
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        return;
    }

    static int progress = 0;
    progress += 5;
    QString msg = QString("HDD:%1:%2").arg(channel.currentCommand).arg(progress);
    serial->write(msg.toUtf8());
    qDebug() << "HDD data sent:" << msg;

    if (progress >= 100) {
        progress = 0;
        setChannelTransmitting(channel, false);
        stopChannelTimer(channel);
        QMessageBox::information(this, "提示",
                                 QString("血透%1流程已完成").arg(channel.currentCommand));
    }
}

// ==================== 连接按钮槽函数 ====================

void Serial_Dialog::on_btn_connect_heart_clicked()
{
    if (m_heartChannel.isConnected) {
        closeSerialPortForChannel(m_heartChannel);
    } else {
        QString portName = m_heartChannel.comboBox->currentData().toString();
        if (portName.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择串口");
            return;
        }
        openSerialPortForChannel(portName, m_heartChannel);
    }
}

void Serial_Dialog::on_btn_connect_bloodPressure_clicked()
{
    if (m_pressureChannel.isConnected) {
        closeSerialPortForChannel(m_pressureChannel);
    } else {
        QString portName = m_pressureChannel.comboBox->currentData().toString();
        if (portName.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择串口");
            return;
        }
        openSerialPortForChannel(portName, m_pressureChannel);
    }
}

void Serial_Dialog::on_btn_connect_breath_clicked()
{
    if (m_breathChannel.isConnected) {
        closeSerialPortForChannel(m_breathChannel);
    } else {
        QString portName = m_breathChannel.comboBox->currentData().toString();
        if (portName.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择串口");
            return;
        }
        openSerialPortForChannel(portName, m_breathChannel);
    }
}

void Serial_Dialog::on_btn_connect_hurry_clicked()
{
    if (m_hurryChannel.isConnected) {
        closeSerialPortForChannel(m_hurryChannel);
    } else {
        QString portName = m_hurryChannel.comboBox->currentData().toString();
        if (portName.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择串口");
            return;
        }
        openSerialPortForChannel(portName, m_hurryChannel);
    }
}

// ==================== 传输按钮槽函数 ====================

void Serial_Dialog::on_btn_heart_clicked()
{
    if (!m_heartChannel.isConnected) {
        return;
    }

    if (m_heartChannel.isTransmitting) {
        setChannelTransmitting(m_heartChannel, false);
        stopChannelTimer(m_heartChannel);
    } else {
        setChannelTransmitting(m_heartChannel, true);
        startChannelTimer(m_heartChannel);
    }
}

void Serial_Dialog::on_btn_bloodPressure_clicked()
{
    if (!m_pressureChannel.isConnected) {
        return;
    }

    if (m_pressureChannel.isTransmitting) {
        setChannelTransmitting(m_pressureChannel, false);
        stopChannelTimer(m_pressureChannel);
    } else {
        setChannelTransmitting(m_pressureChannel, true);
        startChannelTimer(m_pressureChannel);
    }
}

void Serial_Dialog::on_btn_breath_clicked()
{
    QMessageBox::information(this, "提示", "呼吸机控制已由NICU端参数设定驱动，请在NICU端操作锁定/解锁");
}

void Serial_Dialog::on_btn_hurry_clicked()
{
    if (!m_hurryChannel.isConnected) {
        return;
    }

    if (m_hurryChannel.isTransmitting) {
        setChannelTransmitting(m_hurryChannel, false);
        stopChannelTimer(m_hurryChannel);
    } else {
        setChannelTransmitting(m_hurryChannel, true);
        sendHurryData(m_hurryChannel);
    }
}

// ==================== ComboBox切换槽函数 ====================

void Serial_Dialog::on_comboBox_heart_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

void Serial_Dialog::on_comboBox_bloodPressure_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

void Serial_Dialog::on_comboBox_breath_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

void Serial_Dialog::on_comboBox_hurry_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

// ==================== 预留函数（HDD功能） ====================

void Serial_Dialog::on_btn_HDD_clicked()
{
    if (m_hddChannel.isConnected) {
        closeSerialPortForChannel(m_hddChannel);
    } else {
        QString portName = m_hddChannel.comboBox->currentData().toString();
        if (portName.isEmpty()) {
            QMessageBox::warning(this, "错误", "请选择串口");
            return;
        }
        openSerialPortForChannel(portName, m_hddChannel);
    }
}

void Serial_Dialog::on_comboBox_connect_HDD_currentIndexChanged(int index)
{
    Q_UNUSED(index);
}

void Serial_Dialog::on_btn_HDD_2_clicked()
{
    if (!m_hddChannel.isConnected) {
        return;
    }

    if (m_hddChannel.isTransmitting) {
        setChannelTransmitting(m_hddChannel, false);
        stopChannelTimer(m_hddChannel);
    } else {
        m_hddChannel.currentCommand = "check";
        setChannelTransmitting(m_hddChannel, true);
        startChannelTimer(m_hddChannel);
    }
}

// ==================== 获取定时器类型（预留） ====================

Serial_Dialog::TimerType Serial_Dialog::getTimerType(FunctionChannel& channel)
{
    if (&channel == &m_heartChannel) return TimerHeart;
    if (&channel == &m_pressureChannel) return TimerPressure;
    if (&channel == &m_breathChannel) return TimerBreath;
    if (&channel == &m_hurryChannel) return TimerHurry;
    if (&channel == &m_hddChannel) return TimerHDD;
    return TimerHeart;
}