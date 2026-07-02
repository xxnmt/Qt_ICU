#ifndef SERIAL_DIALOG_H
#define SERIAL_DIALOG_H

#include <QMap>
#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// 前置声明Qt类
class QComboBox;
class QPushButton;
class QLabel;

namespace Ui {
class Serial_Dialog;
}

class Serial_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Serial_Dialog(QWidget *parent = 0);
    ~Serial_Dialog();

private slots:
    // 连接按钮槽函数
    void on_btn_connect_heart_clicked();
    void on_btn_connect_bloodPressure_clicked();
    void on_btn_connect_breath_clicked();
    void on_btn_connect_hurry_clicked();
    void on_btn_HDD_clicked();  // 预留

    // ComboBox切换槽函数
    void on_comboBox_heart_currentIndexChanged(int index);
    void on_comboBox_bloodPressure_currentIndexChanged(int index);
    void on_comboBox_breath_currentIndexChanged(int index);
    void on_comboBox_hurry_currentIndexChanged(int index);
    void on_comboBox_connect_HDD_currentIndexChanged(int index);  // 预留

    // 数据传输按钮槽函数
    void on_btn_heart_clicked();
    void on_btn_bloodPressure_clicked();
    void on_btn_breath_clicked();
    void on_btn_hurry_clicked();
    void on_btn_HDD_2_clicked();  // 预留

private:
    Ui::Serial_Dialog *ui;

    // ==================== 数据结构 ====================

    // 功能通道结构体
    struct FunctionChannel {
        QString functionName;           // 功能名称
        QComboBox* comboBox;            // 串口选择器
        QPushButton* connectBtn;        // 连接按钮
        QPushButton* transmitBtn;       // 传输按钮
        QLabel* statusLabel;            // 状态指示灯

        QString selectedPort;           // 当前选择的串口
        bool isConnected;               // 是否已连接
        bool isTransmitting;            // 是否正在传输数据
        int timerId;                    // 定时器ID
        int dataIndex;                  // 数据索引（心跳用）
        QString currentCommand;         // 当前命令（HDD用）

        QString currentVentMode;        // 当前通气模式（呼吸用：VCV/PCV/PSV）
        double tidalVolume;             // 潮气量（ml）
        int respiratoryRate;            // 呼吸频率（次/分）
        double inspiratoryTime;         // 吸气时间（秒）
        double riseTime;                // 升压时间（%）
        double inspiratoryPressure;     // 吸气压力（cmH2O）
        double expiratoryPressure;      // 呼气压力（cmH2O）
        int backupRate;                 // 备用频率（次/分）

        FunctionChannel() {
            comboBox = nullptr;
            connectBtn = nullptr;
            transmitBtn = nullptr;
            statusLabel = nullptr;
            isConnected = false;
            isTransmitting = false;
            timerId = 0;
            dataIndex = 0;
            tidalVolume = 500;
            respiratoryRate = 15;
            inspiratoryTime = 1.0;
            riseTime = 20;
            inspiratoryPressure = 18;
            expiratoryPressure = 5;
            backupRate = 10;
        }
    };

    // 五个功能通道
    FunctionChannel m_heartChannel;
    FunctionChannel m_pressureChannel;
    FunctionChannel m_breathChannel;
    FunctionChannel m_hurryChannel;
    FunctionChannel m_hddChannel;

    // 串口管理：key为端口名，value为串口对象
    QMap<QString, QSerialPort*> m_serialPorts;
    // 串口引用计数：记录每个串口被多少个功能使用
    QMap<QString, int> m_portRefCount;

    // ==================== 辅助函数 ====================

    // 初始化函数
    void initChannels();
    void refreshAllComboBoxes();
    void updateComboBoxList(QComboBox* comboBox);

    // 串口管理
    bool openSerialPortForChannel(const QString& portName, FunctionChannel& channel);
    void closeSerialPortForChannel(FunctionChannel& channel);
    QSerialPort* getSerialPort(const QString& portName);
    bool isPortAvailable(const QString& portName);

    // 通道状态管理
    void updateChannelUI(FunctionChannel& channel);
    void setChannelConnected(FunctionChannel& channel, bool connected);
    void setChannelTransmitting(FunctionChannel& channel, bool transmitting);
    QString getTransmitButtonText(const FunctionChannel& channel) const;

    // 定时器管理
    void startChannelTimer(FunctionChannel& channel);
    void stopChannelTimer(FunctionChannel& channel);
    void timerEvent(QTimerEvent* event) override;

    // 数据发送函数
    void sendHeartData(FunctionChannel& channel);
    void sendPressureData(FunctionChannel& channel);
    void sendBreathData(FunctionChannel& channel);
    void sendHurryData(FunctionChannel& channel);
    void sendHddData(FunctionChannel& channel);

    // 获取通道对应的定时器类型
    enum TimerType {
        TimerHeart = 1,
        TimerPressure = 2,
        TimerBreath = 3,
        TimerHurry = 4,
        TimerHDD = 5
    };
    TimerType getTimerType(FunctionChannel& channel);
};

#endif // SERIAL_DIALOG_H