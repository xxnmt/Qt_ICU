#include "ecgtest_dialog.h"
#include "ui_ecgtest_dialog.h"
#include "user_data.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QFont>
#include <QTimer>

#define DOTS 5

User_Data user(QString::fromUtf8("张依然"), 25);

ECGTest_Dialog::ECGTest_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ECGTest_Dialog)
    , User_serial(nullptr)
    , User_serialflag(false)
    , m_updateTimer(new QTimer(this))
{
    ui->setupUi(this);

    // 1. 设置窗口属性
    setWindowTitle(QString::fromUtf8("心电图"));
    // 暂时去掉无边框以便调试
    // setWindowFlags(Qt::FramelessWindowHint);
    resize(660, 450);

    // 2. 设置白色背景
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);
    this->setAutoFillBackground(true);

    // 3. 初始化用户信息
    ui->label_UserAge->setText(QString::number(user.getAge()));
    ui->label_UserName->setText(user.getName());

    // 4. 读取历史数据
    for (int i = 0; i < 12; i++) {
        User_ChannelData[i] = nullptr;
    }

    QString fileName = ":/hisdata";
    readECGFile(fileName);

    // 5. 初始化串口
    serialPortInit();

    // 6. 定时刷新波形（20fps）
    connect(m_updateTimer, &QTimer::timeout, this, &ECGTest_Dialog::updateWaveform);
    m_updateTimer->start(50);

    qDebug() << "ECGTest_Dialog initialized";
}

ECGTest_Dialog::~ECGTest_Dialog()
{
    User_serial->serialClose();
    for (int i = 0; i < 12; i++) {
        if (User_ChannelData[i]) {
            delete User_ChannelData[i];
            User_ChannelData[i] = nullptr;
        }
    }

    delete ui;
}

void ECGTest_Dialog::readECGFile(QString FileName)
{
    QFile f(FileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "file open fail";
        return;
    }

    QByteArray content = f.readAll();
    User_DataArr = QJsonDocument::fromJson(content).array();
    qDebug() << "hisdata size:" << User_DataArr.size();

    getHistoryData();
}

void ECGTest_Dialog::getHistoryData()
{
    int cols = 2, rows = 6;
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            int index = col * rows + row;
            Heart_Data *tmpHeartData = new Heart_Data();

            if (index < User_DataArr.size()) {
                QJsonObject edata = User_DataArr.at(index).toObject();
                QString channelName = edata["channel"].toString();
                QJsonArray dataArr = edata["value"].toArray();

                tmpHeartData->setChannelName(channelName);
                tmpHeartData->setDataArr(dataArr);
            }

            User_ChannelData[index] = tmpHeartData;
        }
    }
}

// ============================================================
// paintEvent - 所有绘图的入口
// ============================================================
void ECGTest_Dialog::paintEvent(QPaintEvent *event)
{
    int w = this->width();
    int h = this->height();

    if (w <= 0 || h <= 0) {
        return;
    }

    QPainter painter(this);

    // 1. 清除整个背景为白色
    painter.fillRect(0, 0, w, h, Qt::white);

    // 2. 绘制网格
    int topMargin = 0;
    int waveformHeight = h - topMargin;

    // 保存画家状态，设置裁剪区域防止绘制到控件区域
    painter.save();
    painter.setClipRect(0, topMargin, w, waveformHeight);
    painter.translate(0, topMargin);  // 向下偏移

    // 绘制网格和波形（坐标相对于波形区域）
    drawECGGrid(painter, w, waveformHeight, DOTS);
    drawHisECGWave(painter, w, waveformHeight, DOTS);

    if (User_serialflag && !User_newdata.isEmpty()) {
        drawRealTimeWave(painter, w, waveformHeight, DOTS);  // 高亮点会显示！
    }

    painter.restore();

    // 3. 绘制界面信息
    painter.save();
    painter.setPen(QColor(0, 0, 0));
    QFont f("微软雅黑", 9);
    f.setBold(true);
    painter.setFont(f);
    painter.drawText(10, topMargin + 20, "Channel: 12  Speed: 25mm/s");

    if (User_serialflag) {
        painter.setPen(QColor(0, 200, 0));
        painter.drawText(10, topMargin + 40, "● 实时数据");
    } else {
        painter.setPen(QColor(200, 0, 0));
        painter.drawText(10, topMargin + 40, "○ 等待数据...");
    }

    // 显示数据点数
    if (User_ChannelData[0]) {
        painter.setPen(QColor(100, 100, 100));
        QFont smallFont("微软雅黑", 8);
        painter.setFont(smallFont);
        int dataSize = User_ChannelData[0]->getDataArr().size();
        painter.drawText(10, topMargin + 58, QString("数据点数: %1").arg(dataSize));
    }

    painter.restore();

}

// ============================================================
// 绘制网格
// ============================================================
void ECGTest_Dialog::drawECGGrid(QPainter &painter, int width, int height, double dots)
{
    painter.save();

    // 小网格（浅蓝色）
    painter.setPen(QColor(230, 240, 250));
    for (int i = 0; i <= width / DOTS; i++) {
        painter.drawLine(0, i * DOTS, width, i * DOTS);
        painter.drawLine(i * DOTS, 0, i * DOTS, height);
    }

    // 大网格（蓝色）
    painter.setPen(QColor(190, 215, 240));
    for (int i = 0; i <= width / DOTS / 5; i++) {
        painter.drawLine(0, i * DOTS * 5, width, i * DOTS * 5);
        painter.drawLine(i * DOTS * 5, 0, i * DOTS * 5, height);
    }

    painter.restore();
}

// ============================================================
// 绘制历史波形（灰色）
// ============================================================
void ECGTest_Dialog::drawHisECGWave(QPainter &painter, int width, int height, double dots)
{
    painter.save();

    float fpPerMv = 10 * DOTS;
    float fpPerUv = fpPerMv / 1000;

    int rectWidth = width / 2;
    int rowHeight = height / 6;
    int middleHeight = rowHeight / 2;
    int cols = 2;
    int rows = 6;

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            int index = col * rows + row;

            if (index >= 12 || !User_ChannelData[index]) {
                continue;
            }

            QJsonArray data = User_ChannelData[index]->getDataArr();
            int wavelen = data.size();

            if (wavelen == 0) {
                continue;
            }

            // 只显示最新的数据（滚动显示）
            int maxPoints = rectWidth - dots * 2;
            int startIndex = qMax(0, wavelen - maxPoints);

            QVector<QPoint> vecPoints;
            vecPoints.reserve(maxPoints);

            for (int i = startIndex; i < wavelen; i++) {
                if (i - startIndex >= maxPoints) {
                    break;
                }

                int x = col * rectWidth + (i - startIndex);
                double y = row * rowHeight + middleHeight - data[i].toInt() * fpPerUv;
                y = qBound(0.0, y, (double)height);

                vecPoints.append(QPoint(x, (int)y));
            }

            // 绘制通道名称（灰色）
            painter.save();
            painter.setPen(QColor(150, 150, 150));
            painter.drawText(col * rectWidth + 5, row * rowHeight + 20,
                             User_ChannelData[index]->getChannelName());
            painter.restore();

            // 绘制历史波形（浅灰色）
            if (vecPoints.size() > 1) {
                painter.save();
                painter.setPen(QColor(200, 200, 200));
                for (int i = 0; i < vecPoints.size() - 1; i++) {
                    painter.drawLine(vecPoints[i], vecPoints[i + 1]);
                }
                painter.restore();
            }
        }
    }

    painter.restore();
}

// ============================================================
// 绘制实时波形（绿色）
// ============================================================
void ECGTest_Dialog::drawRealTimeWave(QPainter &painter, int width, int height, double dots)
{
    painter.save();

    float fpPerMv = 10 * DOTS;
    float fpPerUv = fpPerMv / 1000;

    int rectWidth = width / 2;
    int rowHeight = height / 6;
    int middleHeight = rowHeight / 2;
    int cols = 2;
    int rows = 6;

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            int index = col * rows + row;

            if (index >= 12 || !User_ChannelData[index]) {
                continue;
            }

            QJsonArray dataArr = User_ChannelData[index]->getDataArr();
            int wavelength = dataArr.size();

            if (wavelength == 0) {
                continue;
            }

            // 获取最新的数据
            int maxPoints = rectWidth - dots * 2;
            int startPoint = qMax(0, wavelength - maxPoints);

            QVector<QPointF> vecPoints;
            vecPoints.reserve(maxPoints);

            for (int i = startPoint; i < wavelength; i++) {
                if (i - startPoint >= maxPoints) {
                    break;
                }

                double x = col * rectWidth + (i - startPoint);
                double y = row * rowHeight + middleHeight - dataArr[i].toInt() * fpPerUv;
                y = qBound(0.0, y, (double)height);

                vecPoints.append(QPointF(x, y));
            }

            // 绘制通道名称（绿色）
            painter.save();
            painter.setPen(QColor(62, 168, 115));
            painter.drawText(col * rectWidth + 5, row * rowHeight + 20,
                             User_ChannelData[index]->getChannelName());
            painter.restore();

            // 绘制实时波形（亮绿色）
            if (vecPoints.size() > 1) {
                painter.save();
                painter.setPen(QColor(62, 168, 115));
                painter.setBrush(Qt::NoBrush);

                for (int i = 0; i < vecPoints.size() - 1; i++) {
                    painter.drawLine(vecPoints[i], vecPoints[i + 1]);
                }

                // 高亮最新的数据点
                if (!vecPoints.isEmpty()) {
                    painter.setPen(QColor(255, 0, 0));
                    painter.setBrush(QColor(255, 0, 0));
                    painter.drawEllipse(vecPoints.last(), 3, 3);
                }

                painter.restore();
            }
        }
    }

    painter.restore();
}

// ============================================================
// 绘制界面信息
// ============================================================
void ECGTest_Dialog::drawInterfaceInfo(QPainter &painter)
{
    painter.save();

    QFont f("微软雅黑", 9);
    f.setBold(true);
    painter.setFont(f);

    // 标题
    painter.setPen(QColor(0, 0, 0));
    int channelnum = 12;
    QString text = QString("Channel: %1  Speed: 25mm/s").arg(channelnum);
    painter.drawText(10, 20, text);

    // 状态指示
    if (User_serialflag) {
        painter.setPen(QColor(0, 200, 0));
        painter.drawText(10, 40, "● 实时数据");
    } else {
        painter.setPen(QColor(200, 0, 0));
        painter.drawText(10, 40, "○ 等待数据...");
    }

    // 数据点数
    if (User_ChannelData[0]) {
        painter.setPen(QColor(100, 100, 100));
        QFont smallFont("微软雅黑", 8);
        painter.setFont(smallFont);
        int dataSize = User_ChannelData[0]->getDataArr().size();
        painter.drawText(10, 58, QString("数据点数: %1").arg(dataSize));
    }

    painter.restore();
}

// ============================================================
// 串口初始化
// ============================================================
bool ECGTest_Dialog::serialPortInit()
{
    User_serial = new Serial_Tool();
    User_serial->m_serialport = new QSerialPort();

    connect(User_serial->m_serialport, &QSerialPort::readyRead,
            this, &ECGTest_Dialog::receiveData);

    bool result = User_serial->serialOpen("com1");
    qDebug() << "Serial port init result:" << result;

    return result;
}

// ============================================================
// 接收串口数据
// ============================================================
void ECGTest_Dialog::receiveData()
{
    if (!User_serial || !User_serial->m_serialport) {
        return;
    }

    QByteArray message = User_serial->m_serialport->readAll();
    if (message.isEmpty()) {
        return;
    }

    qDebug() << "Received:" << message;

    parseSerialData(message);
}

// ============================================================
// 解析串口数据
// ============================================================
void ECGTest_Dialog::parseSerialData(const QByteArray &data)
{
    // 按逗号分割
    QList<QByteArray> parts = data.split(',');

    User_newdata.clear();

    for (const QByteArray &part : parts) {
        // 去除空白字符
        QByteArray trimmed = part.trimmed();
        bool ok;
        int val = trimmed.toInt(&ok);
        if (ok) {
            User_newdata.append(val);
        }
    }

    // 如果数据不足12个，补充0
    while (User_newdata.size() < 12) {
        User_newdata.append(0);
    }

    // 只取前12个
    if (User_newdata.size() > 12) {
        User_newdata = User_newdata.mid(0, 12);
    }

    // 更新到通道数据
    for (int i = 0; i < 12 && i < User_newdata.size(); i++) {
        if (User_ChannelData[i]) {
            User_ChannelData[i]->addData(User_newdata[i]);
        }
    }

    User_serialflag = true;

    // 不在这里调用 repaint，由定时器控制刷新
}

// ============================================================
// 定时刷新波形
// ============================================================
void ECGTest_Dialog::updateWaveform()
{
    update();  // 触发 paintEvent
}

// ============================================================
// 退出按钮
// ============================================================
void ECGTest_Dialog::on_btn_quit_clicked()
{
    //关闭串口
    if (User_serial) {
        User_serial->serialClose();
    }
    close();
}