# NICU 重症监护室设备模拟系统 - 项目文档

> **版本**: v1.0.0 | **日期**: 2026-07-04

## 一、项目概述

本项目是一个基于 Qt 6 的重症监护室（NICU）设备模拟系统，包含心电图仪、血压仪、血液透析仪和呼吸机四个主要医疗设备模块，以及一个配套的数据传输客户端用于模拟串口数据发送。

### 技术栈

- **框架**: Qt 6.11.1 (C++17)
- **UI框架**: Qt Widgets
- **串口通信**: Qt Serial Port
- **图表绘制**: QWT 6.3.0
- **构建工具**: qmake + MinGW 64-bit

---

## 二、项目结构

```
Qt_ICU/
├── NICU/                          # 主应用程序（重症监护室设备模拟器）
│   ├── main.cpp                   # 程序入口
│   ├── NICU.pro                   # Qt 项目配置文件
│   ├── Resource.qrc               # 资源文件配置
│   ├── main_dialog.cpp/h          # 主对话框（功能入口）
│   ├── ecgtest_dialog.cpp/h/ui   # 心电图模块
│   ├── bloodpressure_dialog.cpp/h/ui # 血压仪模块
│   ├── hemodialysis_dialog.cpp/h/ui # 血透仪模块
│   ├── ventilator_dialog.cpp/h/ui # 呼吸机模块
│   ├── bloodpressure.cpp/h        # 血压数据处理类
│   ├── heart_data.cpp/h           # 心电数据类
│   ├── user_data.cpp/h            # 用户数据类
│   ├── serial_tool.cpp/h          # 串口工具类
│   ├── alarm_light.cpp/h          # 报警灯组件
│   ├── plot_data.cpp/h            # QWT 绘图数据类
│   ├── progressbar_round.cpp/h    # 圆形进度条组件
│   ├── progressbar_splash.cpp/h   # 进度条动画组件
│   ├── progressbar_check.cpp/h    # 检查进度条组件
│   ├── All_Header.h              # 头文件汇总
│   ├── build/                     # 构建输出目录
│   └── resource_inside/          # 内部资源文件
├── Transmission/                  # 数据传输客户端
│   ├── main.cpp                  # 程序入口
│   ├── Transmission.pro          # Qt 项目配置文件
│   └── serial_dialog.cpp/h/ui    # 串口数据发送界面
└── resource/                      # 共享资源文件
    ├── images/                   # 图片资源
    └── heartData/                # 心电历史数据
```

---

## 三、总体功能实现方式

### 3.1 系统架构

```
┌───────────────────────────────────────────────────────────┐
│                     Main_Dialog (主界面)                   │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐      │
│  │ 心电图   │ │ 血压仪    │ │ 血透仪    │ │ 呼吸机    │     │
│  └────┬─────┘ └────┬─────┘ └────┬─────┘ └────┬─────┘      │
└───────┼────────────┼────────────┼────────────┼────────────┘
        │            │            │            │
        ▼            ▼            ▼            ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│ECGTest│       │BloodPressure│ │Hemodialysis │ │Ventilator   │
_Dialog│      │ │_Dialog      │ │_Dialog      │ │_Dialog      │
└───────┬─────┘ └───────┬─────┘ └───────┬─────┘ └───────┬─────┘
        │               │               │               │
        ▼               ▼               ▼               ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│Heart_Data   │ │BloodPressure│ │ProgressBar_ │ │Alarm_Light  │
│(12导联数据)  │ │(QWT绘图)    │ │Round/Splash │ │(状态指示灯)  │
└───────┬─────┘ └───────┬─────┘ └─────────────┘ └───────┬─────┘
        │               │                               │
        └───────────────┼───────────────────────────────┘
                        ▼
              ┌─────────────────┐
              │ Serial_Tool     │
              │ (串口通信模块)   │
              └─────────────────┘
```

### 3.2 数据流向

1. **数据传输客户端 (Transmission)** 通过虚拟串口发送模拟医疗数据
2. **NICU 主程序** 通过 `Serial_Tool` 接收串口数据
3. 各设备模块处理接收到的数据并更新 UI 显示

### 3.3 串口通信协议

| 设备 | 串口 | 波特率 | 数据格式 |
|------|------|--------|----------|
| 心电图 | COM1 | 115200 | 12个整数，逗号分隔 |
| 血压仪 | COM3 | 115200 | 3字节（高压/低压/脉搏） |
| 呼吸机 | COM4 | 115200 | `VENT_SET:`（设定参数）、`VENT_STOP`（停止）、`VENT_DATA:`（实时数据）或 'e'（紧急） |
| 血透仪 | COM2 | 115200 | `HDD:<command>`（命令）、`HDD:<command>:<progress>`（进度） |

---

## 四、各模块详细说明

### 4.1 主对话框 (Main_Dialog)

**文件**: `main_dialog.cpp/h`

**功能**: 系统主界面，提供四个医疗设备的入口按钮。

**UI 控件**:
- `btn_Heart` - 心电图按钮
- `btn_Pressure` - 血压仪按钮
- `btn_Blood` - 血透仪按钮
- `btn_Breath` - 呼吸机按钮
- `btn_Quit` - 退出按钮

**核心方法**:
```cpp
void on_btn_Heart_clicked();      // 打开心电图模块
void on_btn_Pressure_clicked();    // 打开血压仪模块
void on_btn_Blood_clicked();       // 打开血透仪模块
void on_btn_Breath_clicked();      // 打开呼吸机模块
void on_btn_Quit_clicked();        // 退出程序
```

**设计要点**:
- 使用 Qt Fusion 风格统一渲染
- 关闭硬件 OpenGL 加速解决显卡驱动问题

---

### 4.2 心电图模块 (ECGTest_Dialog)

**文件**: `ecgtest_dialog.cpp/h/ui`

**功能**: 12导联心电图实时显示，支持历史数据加载和串口实时数据接收。

**核心数据结构**:
- `User_DataArr` - JSON 格式的历史心电图数据
- `User_ChannelData[12]` - 12个导联的数据对象数组
- `User_newdata` - 串口接收到的实时数据
- `User_serialflag` - 串口数据标志
- `m_updateTimer` - 定时器，控制波形刷新频率(50ms)

**核心方法**:
```cpp
void readECGFile(QString FileName);       // 读取历史数据文件
void getHistoryData();                    // 获取历史数据
void drawHisECGWave(QPainter&,int,int,double); // 绘制历史波形
void drawRealTimeWave(QPainter&,int,int,double); // 绘制实时波形
void drawECGGrid(QPainter&,int,int,double);     // 绘制网格
void drawInterfaceInfo(QPainter&);        // 绘制界面信息（通道数、状态指示）
void receiveData();                       // 串口数据接收槽
void parseSerialData(const QByteArray &data); // 解析串口数据
void updateWaveform();                    // 定时刷新波形（触发paintEvent）
bool serialPortInit();                    // 初始化串口
```

**显示布局**:
- 2列 × 6行 = 12个导联显示区域
- 每个导联显示波形曲线和通道名称
- 网格线间距为 5 像素，粗线间隔为 25 像素

**串口通信**:
- 端口: COM1
- 数据格式: `16,12,9,8,6,34,20,22,20,16,12,9`（12个通道数据，逗号分隔）

---

### 4.3 血压仪模块 (BloodPressure_Dialog)

**文件**: `bloodpressure_dialog.cpp/h/ui`

**功能**: 血压数据实时监测，包含高压、低压、脉搏三个参数的数值显示和曲线绘制。

**核心数据结构**:
- `m_bloodPressure` - 血压数据处理对象
- 三个 `QLCDNumber` 显示高压、低压、脉搏

**核心方法**:
```cpp
void initBP();                // 初始化血压数据
void on_btn_quit_clicked();   // 退出并关闭串口
```

**血压处理类 (BloodPressure)**:
**文件**: `bloodpressure.cpp/h`

**功能**: 使用 QWT 库绘制血压曲线，管理三个数据系列（高压/低压/脉搏）。

**核心组件**:
- `QwtPlot` - 绘图控件
- `QwtPlotCurve` - 曲线对象（3条曲线）
- `Plot_Data` - 数据存储类（3个实例）
- `QwtPlotGrid` - 网格
- `QwtPlotPanner` - 平移功能
- `QwtPlotMagnifier` - 缩放功能

**核心方法**:
```cpp
void buildPlot();                     // 构建绘图组件
void drawHistoryData(...);            // 绘制历史数据
void addCurve();                      // 添加曲线
void serialPortInit();                // 初始化串口
void receiveData();                   // 数据接收槽
void updateCurve(QByteArray);         // 更新曲线数据
```

**串口通信**:
- 端口: COM3
- 数据格式: 3字节二进制数据（高压/低压/脉搏）

---

### 4.4 血透仪模块 (Hemodialysis_Dialog)

**文件**: `hemodialysis_dialog.cpp/h/ui`

**功能**: 血液透析流程模拟，包含设备自检、管道连接、清洗、预充、治疗等步骤。

**核心组件**:
- `ProgressBar_Splash` - 进度条动画（用于各步骤进度）
- `ProgressBar_Round` - 圆形进度条（用于填充和开始按钮）
- `QTimer` - 定时器控制进度

**UI 控件**:
- `btn_check` - 自检按钮
- `btn_claen` - 清洗按钮（显示为 claen，应为 clean）
- `btn_connectD` - 连接动脉按钮
- `btn_connectJ` - 连接静脉按钮
- `btn_open` - 开泵按钮
- `btn_fill` - 预充按钮
- `btn_start` - 开始治疗按钮
- `btn_emergency` - 紧急停止按钮

**流程控制**:
```
自检 → 清洗 → 连接动脉 → 连接静脉 → 开泵 → 预充 → 开始治疗
```

**核心方法**:
```cpp
void on_btn_check_clicked();      // 启动自检流程
void on_btn_claen_clicked();      // 启动清洗流程
void on_btn_connectD_clicked();   // 连接动脉
void on_btn_connectJ_clicked();   // 连接静脉
void on_btn_open_clicked();       // 开泵
void on_btn_fill_clicked();       // 预充（圆形进度条）
void on_btn_start_clicked();      // 开始治疗（圆形进度条）
void on_btn_emergency_clicked();  // 紧急停止（红色背景）
void on_btn_quit_clicked();       // 退出按钮
void updateProgress();            // 更新自检进度
void serialPortInit();            // 初始化串口（COM2）
void receiveData();               // 串口数据接收槽
void updateHemoProgress(QString command, int progress); // 更新血透进度
void drawRoundProgress();         // 初始化圆形进度条组件
```

---

### 4.5 呼吸机模块 (Ventilator_Dialog)

**文件**: `ventilator_dialog.cpp/h/ui`

**功能**: 呼吸机监控界面，支持三种通气模式（容量控制VCV、压力控制PCV、压力支持PSV），实现参数设定与实时监测功能。

**核心组件**:
- `Alarm_Light` - 报警灯组件（绿/黄/红/橙四种状态）
- `QMovie` - GIF 动画显示呼吸波形
- `Serial_Tool` - 串口通信

**UI 控件**:
| 控件名称 | 类型 | 功能 |
|----------|------|------|
| `comboBox_ventilationMode` | QComboBox | 通气模式选择（容量控制/压力控制/压力支持） |
| `doubleSpinBox_tidalVolume` | QDoubleSpinBox | 潮气量 |
| `doubleSpinBox_leakageVolume` | QDoubleSpinBox | 漏气量 |
| `doubleSpinBox_minuteVentilation` | QDoubleSpinBox | 每分钟通气量 |
| `spinBox_respiratoryRate` | QSpinBox | 呼吸频率 |
| `doubleSpinBox_inspiratoryTime` | QDoubleSpinBox | 吸气时间 |
| `doubleSpinBox_riseTime` | QDoubleSpinBox | 升压时间 |
| `doubleSpinBox_inspiratoryPressure` | QDoubleSpinBox | 吸气压力 |
| `doubleSpinBox_expiratoryPressure` | QDoubleSpinBox | 呼气压力 |
| `spinBox_backupRate` | QSpinBox | 备用频率 |
| `doubleSpinBox_ieRatio` | QDoubleSpinBox | 呼吸比例 |
| `lab_Gif` | QLabel | 呼吸动画显示 |
| `widget_light` | Alarm_Light | 状态指示灯 |
| `btn_lock` | QPushButton | 锁定/解锁按钮 |

**核心枚举**:
```cpp
enum VentilationMode {
    VCV,  // 容量控制
    PCV,  // 压力控制
    PSV   // 压力支持
};

enum ParamType {
    SET_PARAM,      // 设定参数
    MONITOR_PARAM,  // 监测参数
    DERIVED_PARAM,  // 派生参数
    NA_PARAM        // 不适用
};
```

**核心方法**:
```cpp
void showGif();                          // 显示呼吸动画
void serialportInit();                   // 初始化串口
void alarmLight();                       // 初始化报警灯
void updateLight();                      // 灯状态切换槽
void receiveData();                      // 串口数据接收槽
void switchMode(VentilationMode mode);   // 切换通气模式
void updateParamStatus(...);             // 更新参数可编辑状态
void sendSetParams();                    // 发送设定参数
ParamType getParamType(...);             // 获取参数类型
```

**参数分类表**:
| 参数 | 容量控制(VCV) | 压力控制(PCV) | 压力支持(PSV) |
|------|:-------------:|:-------------:|:-------------:|
| 潮气量 | **设定** | 监测(500±10) | 监测(500±10) |
| 漏气量 | 监测(20±4) | 监测(20±4) | 监测(20±4) |
| 每分钟通气量 | **派生**(计算) | **派生**(计算) | **派生**(计算) |
| 呼吸频率 | **设定** | **设定** | 监测(13~20) |
| 吸气时间 | **设定** | **设定** | **派生**(0.6~1.8) |
| 升压时间 | N/A(隐藏) | **设定** | **设定** |
| 吸气压力 | 监测(16±3) | **设定** | **设定** |
| 呼气压力 | **设定** | **设定** | **设定** |
| 备用频率 | **设定** | **设定** | **设定** |
| 呼吸比例 | **派生**(计算) | **派生**(计算) | **派生**(计算) |

**参数类型定义**:
- **设定参数**: 医生手动输入，解锁状态下可编辑
- **监测参数**: 设备传感器测量，实时更新，始终只读
- **派生参数**: 由其他参数计算得出，始终只读
- **N/A**: 该模式下不适用，控件隐藏

**锁定机制**:
- `btn_lock` 控制整个界面的可编辑状态
- 锁定状态：所有设定参数和通气模式下拉框不可编辑
- 解锁状态：设定参数可编辑，通气模式可切换
- 监测参数和派生参数始终只读，不受锁定状态影响
- 锁定时自动发送当前设定参数到 Transmission

**灯状态说明**:
| 状态 | 颜色 | 含义 |
|------|------|------|
| 0→1 | 绿→黄 | 正常工作状态循环 |
| 2→3 | 红→橙 | 紧急状态循环（接收到 'e' 信号） |

**串口通信**:
- 端口: COM4

**NICU → Transmission（设定参数）**:
```
格式: VENT_SET:<mode>:<tidalVolume>:<respRate>:<inspTime>:<riseTime>:<inspPressure>:<expPressure>:<backupRate>
示例: VENT_SET:VCV:500:15:1.0:0:18:5:10
```

**NICU → Transmission（停止命令）**:
```
格式: VENT_STOP
说明: 解锁时发送，停止数据传输
```

**Transmission → NICU（实时数据）**:
```
格式: VENT_DATA:<mode>:<tidalVolume>:<leak>:<minuteVol>:<respRate>:<inspTime>:<riseTime>:<inspPressure>:<expPressure>:<backupRate>:<ieRatio>
示例: VENT_DATA:VCV:500:18:7.5:15:1.0:0:17:5:10:0.5
```

---

## 五、公共组件

### 5.1 串口工具类 (Serial_Tool)

**文件**: `serial_tool.cpp/h`

**功能**: 封装串口通信功能，提供打开/关闭串口方法。

**核心方法**:
```cpp
bool serialOpen(QString com);    // 打开指定串口
void serialClose();              // 关闭串口
```

**成员变量**:
- `m_serialport` - QSerialPort 对象指针

**配置参数**:
- 波特率: 115200
- 数据位: 8
- 校验位: 无
- 停止位: 1

---

### 5.2 用户数据类 (User_Data)

**文件**: `user_data.cpp/h`

**功能**: 存储患者基本信息（姓名、年龄）。

**核心方法**:
```cpp
void setName(QString);           // 设置姓名
void setAge(int);                // 设置年龄
QString getName();               // 获取姓名
int getAge();                    // 获取年龄
```

**全局实例**:
```cpp
extern User_Data user;           // 在 ecgtest_dialog.cpp 中定义
```

---

### 5.3 心电数据类 (Heart_Data)

**文件**: `heart_data.cpp/h`

**功能**: 存储单个导联的心电图数据。

**核心方法**:
```cpp
void setChannelName(QString);    // 设置通道名称
void setDataArr(QJsonArray);     // 设置数据数组
void addData(int);               // 添加新数据点
QString getChannelName() const;  // 获取通道名称
QJsonArray getDataArr() const;   // 获取数据数组
```

**成员变量**:
- `User_ChannelName` - 通道名称
- `User_DataArr` - 数据数组（QJsonArray）

**数据管理**:
- 最大存储 310 个数据点（MAX_DATA）
- 超过限制时自动移除最旧数据

---

### 5.4 报警灯组件 (Alarm_Light)

**文件**: `alarm_light.cpp/h`

**功能**: 自定义圆形指示灯组件，支持四种颜色状态。

**核心方法**:
```cpp
void setRedLight();              // 设置红色
void setYellowLight();           // 设置黄色
void setGreenLight();            // 设置绿色
void setOrangeLight();           // 设置橙色
void setBackgroundColor(QColor); // 设置背景色
```

**绘制方式**:
- 使用 QPainter 绘制圆形
- 外层边框使用渐变效果
- 内层为实心圆形

---

### 5.5 绘图数据类 (Plot_Data)

**文件**: `plot_data.cpp/h`

**功能**: 继承 QwtSeriesData，提供数据点存储和访问接口。

**核心方法**:
```cpp
size_t size() const;             // 返回数据点数量
QPointF sample(size_t i) const;  // 返回第i个数据点
void setParam(int, double);      // 设置采样参数
void addBaseData(quint64, QVector<unsigned char>); // 添加历史数据
bool updateCurveData(unsigned char); // 更新单个数据点
QwtInterval getXInterval();      // 获取X轴范围
```

**成员变量**:
- `m_value` - 数据点向量（QVector<QPointF>）
- `m_sampleRate` - 采样率（Hz）
- `m_xWidth` - X轴显示宽度（秒）
- `m_maxCount` - 最大数据点数

---

### 5.6 圆形进度条组件 (ProgressBar_Round)

**文件**: `progressbar_round.cpp/h`

**功能**: 自定义圆形进度条，支持动画效果。

**核心方法**:
```cpp
void setValue(float);            // 设置进度值（带动画）
void setInColor(QColor);         // 设置内部颜色
void setOutColor(QColor);        // 设置外部颜色
void paintOutterBar(QPainter&);  // 绘制外圈
void paintInnerBar(QPainter&);   // 绘制内圈（进度）
void paintText(QPainter&);       // 绘制百分比文字
```

**特性**:
- 使用 QPropertyAnimation 实现平滑动画
- 进度范围: 0-100
- 动画时长: 2000ms

---

### 5.7 进度条动画组件 (ProgressBar_Splash)

**文件**: `progressbar_splash.cpp/h`

**功能**: 基于 QSplashScreen 的进度条动画，用于血透仪各步骤。

**核心方法**:
```cpp
void generateNumber();           // 生成 1-100 数字列表
void updateProgress();           // 更新进度
void timerEvent(QTimerEvent*);   // 定时器事件处理
```

**构造参数**:
- `time` - 总时长（毫秒）
- `progressbar` - 关联的 QProgressBar 控件
- `btn` - 进度完成后启用的按钮（可为 NULL）

---

### 5.8 检查进度条组件 (ProgressBar_Check)

**文件**: `progressbar_check.cpp/h`

**功能**: 自定义进度条，使用图片绘制背景和进度条。

**核心方法**:
```cpp
void PaintEvent(QPaintEvent*);   // 绘制进度条
```

**绘制方式**:
- 背景: `:/resource_inside/images/progress_back.png`
- 进度: `:/resource_inside/images/progress_front.png`
- 右侧显示百分比文字

---

## 六、数据传输客户端 (Transmission)

**文件**: `serial_dialog.cpp/h/ui`

**功能**: 模拟医疗设备数据发送，支持五个功能通道的串口数据传输，包括呼吸机三模式数据模拟。

**核心数据结构**:
```cpp
struct FunctionChannel {
    QString functionName;        // 功能名称
    QComboBox* comboBox;         // 串口选择器
    QPushButton* connectBtn;     // 连接按钮
    QPushButton* transmitBtn;    // 传输按钮
    QLabel* statusLabel;         // 状态指示灯
    QString selectedPort;        // 当前串口
    bool isConnected;            // 连接状态
    bool isTransmitting;         // 传输状态
    int timerId;                 // 定时器ID
    int dataIndex;               // 数据索引（心跳用）
    QString currentCommand;      // 当前命令（HDD用）
    
    // 呼吸机专用字段
    QString currentVentMode;     // 当前通气模式（VCV/PCV/PSV）
    double tidalVolume;          // 潮气量（ml）
    int respiratoryRate;         // 呼吸频率（次/分）
    double inspiratoryTime;      // 吸气时间（秒）
    double riseTime;             // 升压时间（%）
    double inspiratoryPressure;  // 吸气压力（cmH2O）
    double expiratoryPressure;   // 呼气压力（cmH2O）
    int backupRate;              // 备用频率（次/分）
};
```

**功能通道**:
| 通道 | 功能 | 定时器间隔 | 数据格式 |
|------|------|-----------|----------|
| m_heartChannel | 心跳/心电图 | 200ms | 12个整数，逗号分隔 |
| m_pressureChannel | 血压 | 1000ms | 3字节二进制 |
| m_breathChannel | 呼吸机 | 1000ms | `VENT_DATA:<参数列表>` |
| m_hurryChannel | 紧急 | 单次发送 | 'e' 字符 |
| m_hddChannel | 血透仪 | 100ms | `HDD:<command>:<progress>` |

**串口管理**:
- 使用 `QMap<QString, QSerialPort*>` 管理串口对象
- 使用引用计数 `QMap<QString, int>` 支持串口共享
- 心跳和血压不允许共享串口
- 呼吸、紧急和血透之间可以共享串口

**呼吸机三模式数据模拟算法**:

**VCV模式（容量控制）**:
- 潮气量 = 设定值（不波动）
- 吸气压力 = 16 ± 3（模拟传感器测量）
- 漏气量 = 20 ± 4（模拟传感器测量）
- 每分钟通气量 = 潮气量 × 呼吸频率 / 1000（计算得出）
- 呼吸比例 = 吸气时间 / (呼吸周期 - 吸气时间)（计算得出）
- 升压时间 = 0（不适用，隐藏）

**PCV模式（压力控制）**:
- 吸气压力 = 设定值
- 潮气量 = 500 ± 10（模拟传感器测量）
- 漏气量 = 20 ± 4（模拟传感器测量）
- 每分钟通气量 = 潮气量 × 呼吸频率 / 1000（计算得出）
- 呼吸比例 = 吸气时间 / (呼吸周期 - 吸气时间)（计算得出）

**PSV模式（压力支持）**:
- 吸气压力 = 设定值
- 潮气量 = 500 ± 10（模拟传感器测量）
- 呼吸频率 = 13 ~ 20（模拟传感器测量）
- 吸气时间 = 0.6 ~ 1.8秒（模拟传感器测量）
- 漏气量 = 20 ± 4（模拟传感器测量）
- 每分钟通气量 = 潮气量 × 呼吸频率 / 1000（计算得出）
- 呼吸比例 = 吸气时间 / (呼吸周期 - 吸气时间)（计算得出）

**核心方法**:
```cpp
void initChannels();                 // 初始化通道
void openSerialPortForChannel(...);  // 打开串口
void closeSerialPortForChannel(...); // 关闭串口
void startChannelTimer(...);         // 启动定时器
void stopChannelTimer(...);          // 停止定时器
void sendHeartData(...);             // 发送心跳数据
void sendPressureData(...);          // 发送血压数据
void sendBreathData(...);            // 发送呼吸机数据（三模式）
void sendHurryData(...);             // 发送紧急信号
void sendHddData(...);               // 发送血透进度数据
```

**串口接收处理**:
- 在 `readyRead` 信号中检测 `VENT_SET:` 协议
- 解析设定参数并更新 `m_breathChannel` 字段
- 自动启动定时器发送实时数据
- 检测 `VENT_STOP` 命令，停止定时器并停止数据传输

---

## 七、资源文件

### 7.1 图片资源

| 图片 | 用途 |
|------|------|
| back.png | 返回按钮 |
| blood.png | 血液相关图标 |
| breath.png | 呼吸相关图标 |
| breathgif.gif | 呼吸动画 |
| heart.png | 心脏图标 |
| pressure.png | 血压图标 |
| progress_back.png | 进度条背景 |
| progress_front.png | 进度条前景 |
| lock/unlock.png | 锁定按钮图标 |
| quit.png | 退出按钮图标 |

### 7.2 数据资源

- `hisdata.txt` - 心电图历史数据（JSON 格式）

---

## 八、已知问题与改进建议

### 8.1 已修复问题

1. **心电图索引越界崩溃**: 在 `drawHisECGWave()` 和 `updateECGWave()` 中添加了边界检查（`i < User_newdata.size()`），防止访问超出列表范围的元素

2. **心电数据空指针崩溃**: 修改 `readECGFile()`，确保即使文件打开失败也调用 `getHistoryData()`，初始化所有12个 `User_ChannelData` 元素

3. **血透仪进度只到95%**: 已修复 `sendHddData()` 中的发送顺序，改为先增加进度再发送，确保100%能被正确发送

4. **呼吸机参数分类**: 实现了完整的三模式参数分类逻辑，支持设定参数、监测参数、派生参数和N/A参数的正确显示和锁定控制

5. **呼吸机模拟算法修正**: 修正了VCV模式下潮气量不应波动的问题，统一了漏气量模拟范围(20±4)，调整了PSV模式呼吸频率(13~20)和吸气时间(0.6~1.8)范围

6. **呼吸机数据传输控制**: 添加了VENT_STOP命令支持，解锁时停止数据传输，锁定时重新启动；修正了receiveData()按模式区分更新，设定参数不再被模拟数据覆盖

### 8.2 代码问题

1. **血透仪按钮拼写错误**: `btn_claen` 应为 `btn_clean`
2. **资源路径不一致**: NICU 使用 `:/resource/` 和 `:/resource_inside/` 两个前缀
3. **内存泄漏**: 主对话框中创建的子对话框未在关闭时删除
4. **串口未打开检查**: 部分模块在串口未打开时尝试写入数据

### 8.3 改进建议

1. **统一资源管理**: 使用单一资源前缀，整理资源文件结构
2. **内存管理优化**: 使用 `QScopedPointer` 或智能指针管理动态分配对象
3. **串口状态检查**: 在写入前检查串口是否打开
4. **日志系统**: 添加日志记录功能，便于调试和问题追踪
5. **错误处理**: 完善异常处理和错误提示
6. **配置文件**: 将串口配置等参数移至配置文件
7. **数据验证**: 添加数据格式验证，防止非法数据导致崩溃
8. **呼吸机参数范围限制**: 为各参数添加合理的最小值和最大值限制

---

## 九、编译与运行

### 9.1 编译环境

- Qt 6.11.1 (MinGW 64-bit)
- QWT 6.3.0（需安装并配置 INCLUDEPATH 和 LIBS）

### 9.2 编译步骤

1. 打开 Qt Creator，导入 `NICU.pro` 或 `Transmission.pro`
2. 配置构建套件为 Desktop Qt 6.11.1 MinGW 64-bit
3. 构建项目（Debug 或 Release）
4. 运行生成的可执行文件

### 9.3 运行前准备

1. 安装虚拟串口驱动（如 Virtual Serial Port Driver）
2. 创建虚拟串口对（如 COM3 ↔ COM4）
3. 先运行 Transmission 客户端，连接相应串口
4. 再运行 NICU 主程序

---

## 十、版本信息

| 项目 | 版本 | 说明 |
|------|------|------|
| Qt | 6.11.1 | 主框架版本 |
| QWT | 6.3.0 | 图表绘制库 |
| C++ | C++17 | 语言标准 |
| 构建工具 | qmake | Qt 项目构建工具 |

---

## 十一、资源文件说明

### 11.1 资源路径

NICU 项目使用以下资源前缀：

| 前缀 | 路径 | 用途 |
|------|------|------|
| `:/hisdata` | resource_inside/hisdata.txt | 心电图历史数据 |
| `:/resource_inside/images/` | resource_inside/images/ | 内部图片资源（如呼吸动画、锁定图标） |

### 11.2 图片资源

| 图片 | 用途 |
|------|------|
| back.png | 返回按钮 |
| blood.png | 血液相关图标 |
| breath.png | 呼吸相关图标 |
| breathgif.gif | 呼吸动画 |
| heart.png | 心脏图标 |
| pressure.png | 血压图标 |
| progress_back.png | 进度条背景 |
| progress_front.png | 进度条前景 |
| lock/unlock.png | 锁定按钮图标 |
| quit.png | 退出按钮图标 |

### 11.3 数据资源

- `hisdata.txt` - 心电图历史数据（JSON 格式）

---

## 十二、相关文档

| 文档名称 | 描述 |
|----------|------|
| [README.md](../README.md) | 项目简介和快速开始指南 |
| [开发计划](development_plan.md) | 项目开发计划、进度安排、资源需求 |
| [需求规格说明](requirements_specification.md) | 完整需求规格说明文档 |
| [软件设计说明](software_design.md) | 系统架构设计、模块设计、算法设计 |
| [软件测试报告](test_report.md) | 测试用例、缺陷记录、测试结论 |
