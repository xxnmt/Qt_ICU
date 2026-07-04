# NICU 重症监护室设备模拟系统 - 软件设计说明

> **版本**: v1.0.0 | **日期**: 2026-07-04

## 1. 概述

### 1.1 设计目标

本系统采用模块化设计，基于 Qt 6 框架实现重症监护室设备模拟功能。设计目标包括：

1. **模块化架构**：各设备模块独立设计，便于维护和扩展
2. **串口通信**：采用 Qt Serial Port 实现可靠的串口数据传输
3. **实时显示**：确保数据采集和显示的流畅性
4. **参数管理**：支持参数设定、监测和派生的分类管理
5. **错误处理**：具备完善的异常处理和错误提示机制

### 1.2 架构概述

系统采用客户端-服务器架构，分为两个主要部分：

1. **NICU 主程序**：作为客户端，负责数据接收、处理和显示
2. **Transmission 客户端**：作为服务器端，负责模拟硬件设备发送数据

两者通过虚拟串口进行通信，实现数据的双向传输。

## 2. 系统架构设计

### 2.1 分层架构

```
┌───────────────────────────────────────────────────────────┐
│                    UI 层 (Qt Widgets)                     │
│  Main_Dialog  ECG_Dialog  BP_Dialog  HD_Dialog  VENT_Dialog│
└───────────────────────────┬───────────────────────────────┘
                            │
┌───────────────────────────▼───────────────────────────────┐
│                   业务逻辑层                              │
│  Heart_Data  BloodPressure  ProgressBar  Alarm_Light      │
└───────────────────────────┬───────────────────────────────┘
                            │
┌───────────────────────────▼───────────────────────────────┐
│                   数据访问层                              │
│              Serial_Tool  User_Data                       │
└───────────────────────────┬───────────────────────────────┘
                            │
┌───────────────────────────▼───────────────────────────────┐
│                    串口通信层                             │
│                Qt Serial Port                            │
└───────────────────────────────────────────────────────────┘
```

### 2.2 模块划分

| 模块 | 功能 | 文件 |
|------|------|------|
| 主对话框 | 系统入口，设备选择 | main_dialog.cpp/h |
| 心电图 | 12导联波形显示 | ecgtest_dialog.cpp/h |
| 血压仪 | 血压监测与曲线显示 | bloodpressure_dialog.cpp/h |
| 血透仪 | 透析流程模拟 | hemodialysis_dialog.cpp/h |
| 呼吸机 | 通气模式模拟 | ventilator_dialog.cpp/h |
| 串口工具 | 串口通信封装 | serial_tool.cpp/h |
| 数据传输 | 数据模拟发送 | serial_dialog.cpp/h |

### 2.3 数据流向

```
Transmission (模拟硬件)
       │
       ▼ (串口发送)
┌─────────────────┐
│  Serial_Tool    │
│  (串口接收)      │
└────────┬────────┘
         │
    ┌────┼────┬──────────┬─────────────┐
    ▼    ▼    ▼          ▼             ▼
 ECG   BP   HDialog  VENT_Dialog  其他模块
```

## 3. 模块详细设计

### 3.1 主对话框模块 (Main_Dialog)

**类设计**:

| 类名 | 职责 | 父类 |
|------|------|------|
| Main_Dialog | 系统主界面，提供设备入口 | QDialog |

**成员变量**:

| 变量名 | 类型 | 描述 |
|--------|------|------|
| ui | Ui::Main_Dialog* | UI 对象 |

**核心方法**:

| 方法名 | 功能 | 参数 | 返回值 |
|--------|------|------|--------|
| on_btn_Heart_clicked() | 打开心电图模块（创建局部 ECGTest_Dialog 对象） | 无 | void |
| on_btn_Pressure_clicked() | 打开血压仪模块（创建局部 BloodPressure_Dialog 对象） | 无 | void |
| on_btn_Blood_clicked() | 打开血透仪模块（创建局部 Hemodialysis_Dialog 对象） | 无 | void |
| on_btn_Breath_clicked() | 打开呼吸机模块（创建局部 Ventilator_Dialog 对象） | 无 | void |
| on_btn_Quit_clicked() | 退出程序 | 无 | void |

### 3.2 心电图模块 (ECGTest_Dialog)

**类设计**:

| 类名 | 职责 | 父类 |
|------|------|------|
| ECGTest_Dialog | 心电图显示界面 | QDialog |
| Heart_Data | 心电数据管理 | QObject |

**核心数据结构**:

```cpp
Heart_Data* User_ChannelData[12];    // 12导联数据对象数组
QJsonArray User_DataArr;              // JSON格式历史数据
QList<int> User_newdata;              // 串口接收到的实时数据
bool User_serialflag;                 // 串口数据标志
QTimer* m_updateTimer;                // 定时器，控制波形刷新频率(50ms)
```

**核心方法**:

| 方法名 | 功能 | 参数 | 返回值 |
|--------|------|------|--------|
| readECGFile() | 读取历史数据文件 | QString FileName | void |
| getHistoryData() | 获取历史数据 | 无 | void |
| drawHisECGWave() | 绘制历史波形 | QPainter&, int, int, double | void |
| drawRealTimeWave() | 绘制实时波形 | QPainter&, int, int, double | void |
| drawECGGrid() | 绘制网格背景 | QPainter&, int, int, double | void |
| drawInterfaceInfo() | 绘制界面信息（通道数、状态指示） | QPainter& | void |
| receiveData() | 串口数据接收槽 | 无 | void |
| parseSerialData() | 解析串口数据 | const QByteArray &data | void |
| updateWaveform() | 定时刷新波形（触发paintEvent） | 无 | void |
| serialPortInit() | 初始化串口（COM1） | 无 | bool |

**显示布局**:

- 2列 × 6行 = 12个导联显示区域
- 每个导联显示波形曲线和通道名称
- 网格线间距为 5 像素，粗线间隔为 25 像素

### 3.3 血压仪模块 (BloodPressure_Dialog)

**类设计**:

| 类名 | 职责 | 父类 |
|------|------|------|
| BloodPressure_Dialog | 血压监测界面 | QDialog |
| BloodPressure | 血压数据处理和绘图 | QWidget |
| Plot_Data | 绘图数据存储 | QwtSeriesData |

**核心组件**:

| 组件 | 类型 | 功能 |
|------|------|------|
| m_bloodPressure | BloodPressure* | 血压处理对象 |
| lcd_high | QLCDNumber* | 高压显示 |
| lcd_low | QLCDNumber* | 低压显示 |
| lcd_pulse | QLCDNumber* | 脉搏显示 |

**核心方法**:

| 方法名 | 功能 | 参数 | 返回值 |
|--------|------|------|--------|
| initBP() | 初始化血压数据 | 无 | void |
| buildPlot() | 构建绘图组件 | 无 | void |
| receiveData() | 数据接收槽 | 无 | void |
| updateCurve() | 更新曲线数据 | QByteArray | void |

**图表功能**:

- 使用 QwtPlot 绘制三条曲线（高压/低压/脉搏）
- 支持平移（QwtPlotPanner）
- 支持缩放（QwtPlotMagnifier）

### 3.4 血透仪模块 (Hemodialysis_Dialog)

**类设计**:

| 类名 | 职责 | 父类 |
|------|------|------|
| Hemodialysis_Dialog | 血透流程界面 | QDialog |
| ProgressBar_Splash | 进度条动画 | QSplashScreen |
| ProgressBar_Round | 圆形进度条 | QWidget |

**核心组件**:

| 组件 | 类型 | 功能 |
|------|------|------|
| m_timer | QTimer* | 定时器 |
| m_splash | ProgressBar_Splash* | 进度条动画 |
| m_fillBar | ProgressBar_Round* | 预充进度条 |
| m_startBar | ProgressBar_Round* | 治疗进度条 |

**流程控制**:

```
自检 → 清洗 → 连接动脉 → 连接静脉 → 开泵 → 预充 → 开始治疗
```

**核心方法**:

| 方法名 | 功能 | 参数 | 返回值 |
|--------|------|------|--------|
| on_btn_check_clicked() | 启动自检 | 无 | void |
| on_btn_claen_clicked() | 启动清洗 | 无 | void |
| on_btn_connectD_clicked() | 连接动脉 | 无 | void |
| on_btn_connectJ_clicked() | 连接静脉 | 无 | void |
| on_btn_open_clicked() | 开泵 | 无 | void |
| on_btn_fill_clicked() | 启动预充 | 无 | void |
| on_btn_start_clicked() | 开始治疗 | 无 | void |
| on_btn_emergency_clicked() | 紧急停止 | 无 | void |
| on_btn_quit_clicked() | 退出按钮 | 无 | void |
| serialPortInit() | 初始化串口（COM2） | 无 | void |
| receiveData() | 串口数据接收槽 | 无 | void |
| updateHemoProgress() | 更新血透进度 | QString command, int progress | void |
| drawRoundProgress() | 初始化圆形进度条组件 | 无 | void |

### 3.5 呼吸机模块 (Ventilator_Dialog)

**类设计**:

| 类名 | 职责 | 父类 |
|------|------|------|
| Ventilator_Dialog | 呼吸机监控界面 | QDialog |
| Alarm_Light | 报警灯组件 | QWidget |

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

**参数分类表**:

| 参数 | VCV | PCV | PSV |
|------|:---:|:---:|:---:|
| 潮气量 | SET | MON(500±10) | MON(500±10) |
| 漏气量 | MON(20±4) | MON(20±4) | MON(20±4) |
| 每分钟通气量 | DER | DER | DER |
| 呼吸频率 | SET | SET | MON(13~20) |
| 吸气时间 | SET | SET | DER(0.6~1.8) |
| 升压时间 | NA | SET | SET |
| 吸气压力 | MON(16±3) | SET | SET |
| 呼气压力 | SET | SET | SET |
| 备用频率 | SET | SET | SET |
| 呼吸比例 | DER | DER | DER |

**核心方法**:

| 方法名 | 功能 | 参数 | 返回值 |
|--------|------|------|--------|
| switchMode() | 切换通气模式 | VentilationMode mode | void |
| sendSetParams() | 发送设定参数 | 无 | void |
| receiveData() | 接收实时数据 | 无 | void |
| getParamType() | 获取参数类型 | VentilationMode, QString | ParamType |
| updateParamStatus() | 更新参数状态 | QString, ParamType | void |

**锁定机制**:

- `btn_lock` 控制界面可编辑状态
- 锁定时：设定参数不可编辑，发送参数到 Transmission
- 解锁时：设定参数可编辑，发送 VENT_STOP 停止数据传输
- 监测参数和派生参数始终只读

## 4. 数据结构设计

### 4.1 心电数据结构 (Heart_Data)

```cpp
class Heart_Data {
public:
    QString User_ChannelName;    // 通道名称
    QJsonArray User_DataArr;     // 数据数组
    static const int MAX_DATA = 310;  // 最大数据点数
};
```

### 4.2 用户数据结构 (User_Data)

```cpp
class User_Data {
public:
    QString getName();
    int getAge();
    void setName(QString);
    void setAge(int);
private:
    QString name;
    int age;
};
```

### 4.3 功能通道结构 (FunctionChannel)

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
    int dataIndex;               // 数据索引
    QString currentCommand;      // 当前命令
    
    // 呼吸机专用字段
    QString currentVentMode;     // 通气模式
    double tidalVolume;          // 潮气量
    int respiratoryRate;         // 呼吸频率
    double inspiratoryTime;      // 吸气时间
    double riseTime;             // 升压时间
    double inspiratoryPressure;  // 吸气压力
    double expiratoryPressure;   // 呼气压力
    int backupRate;              // 备用频率
};
```

### 4.4 绘图数据结构 (Plot_Data)

```cpp
class Plot_Data : public QwtSeriesData<QPointF> {
public:
    QVector<QPointF> m_value;    // 数据点向量
    int m_sampleRate;            // 采样率(Hz)
    int m_xWidth;                // X轴宽度(秒)
    int m_maxCount;              // 最大数据点数
};
```

## 5. 接口设计

### 5.1 串口工具类接口 (Serial_Tool)

```cpp
class Serial_Tool {
public:
    bool serialOpen(QString com);    // 打开串口
    void serialClose();              // 关闭串口
    QSerialPort* m_serialport;       // 串口对象
};
```

### 5.2 呼吸机串口协议

**NICU → Transmission**:

| 命令 | 格式 | 说明 |
|------|------|------|
| VENT_SET | `VENT_SET:<mode>:<tidalVolume>:<respRate>:<inspTime>:<riseTime>:<inspPressure>:<expPressure>:<backupRate>` | 发送设定参数 |
| VENT_STOP | `VENT_STOP` | 停止数据传输 |

**Transmission → NICU**:

| 命令 | 格式 | 说明 |
|------|------|------|
| VENT_DATA | `VENT_DATA:<mode>:<tidalVolume>:<leak>:<minuteVol>:<respRate>:<inspTime>:<riseTime>:<inspPressure>:<expPressure>:<backupRate>:<ieRatio>` | 实时数据 |
| e | `e` | 紧急信号 |

### 5.3 血透仪串口协议

**NICU → Transmission**:

| 命令 | 格式 | 说明 |
|------|------|------|
| HDD | `HDD:<command>` | 发送命令 |

**Transmission → NICU**:

| 命令 | 格式 | 说明 |
|------|------|------|
| HDD | `HDD:<command>:<progress>` | 进度数据 |

## 6. 算法设计

### 6.1 呼吸机数据模拟算法

**VCV模式**:
```
tidalVol = channel.tidalVolume;                    // 设定值
respRate = channel.respiratoryRate;                // 设定值
inspTime = channel.inspiratoryTime;                // 设定值
inspPressure = 16 + (rand() % 7 - 3);              // 监测值
leak = 20 + (rand() % 9 - 4);                      // 监测值
minuteVol = tidalVol * respRate / 1000;            // 计算值
ieRatio = inspTime / (60/respRate - inspTime);     // 计算值
```

**PCV模式**:
```
inspPressure = channel.inspiratoryPressure;        // 设定值
respRate = channel.respiratoryRate;                // 设定值
inspTime = channel.inspiratoryTime;                // 设定值
riseTime = channel.riseTime;                       // 设定值
tidalVol = 500 + (rand() % 21 - 10);              // 监测值
leak = 20 + (rand() % 9 - 4);                      // 监测值
minuteVol = tidalVol * respRate / 1000;            // 计算值
ieRatio = inspTime / (60/respRate - inspTime);     // 计算值
```

**PSV模式**:
```
inspPressure = channel.inspiratoryPressure;        // 设定值
riseTime = channel.riseTime;                       // 设定值
tidalVol = 500 + (rand() % 21 - 10);              // 监测值
respRate = 13 + rand() % 8;                        // 监测值
inspTime = 0.6 + (rand() % 13) * 0.1;              // 派生值
leak = 20 + (rand() % 9 - 4);                      // 监测值
minuteVol = tidalVol * respRate / 1000;            // 计算值
ieRatio = inspTime / (60/respRate - inspTime);     // 计算值
```

### 6.2 心电图波形绘制算法

```
1. 读取历史数据或实时数据
2. 计算波形偏移量和缩放比例
3. 绘制网格背景
4. 逐点绘制波形曲线
5. 处理数据边界，防止越界访问
```

### 6.3 血透仪进度算法

```
1. 启动定时器，设置间隔时间
2. 每次定时器触发，增加进度值
3. 更新进度条显示
4. 进度达到100%时，停止定时器，启用下一步按钮
```

## 7. UI 设计

### 7.1 主界面设计

| 控件 | 类型 | 位置 | 功能 |
|------|------|------|------|
| btn_Heart | QPushButton | 左上 | 心电图入口 |
| btn_Pressure | QPushButton | 右上 | 血压仪入口 |
| btn_Blood | QPushButton | 左下 | 血透仪入口 |
| btn_Breath | QPushButton | 右下 | 呼吸机入口 |
| btn_Quit | QPushButton | 底部 | 退出程序 |

### 7.2 心电图界面设计

- 12导联波形显示区域（2×6网格）
- 网格背景和通道名称标签
- 患者信息显示（姓名、年龄）

### 7.3 血压仪界面设计

- 三个 QLCDNumber 显示高压、低压、脉搏
- QwtPlot 曲线图表显示历史趋势
- 患者信息显示

### 7.4 血透仪界面设计

- 流程按钮区域（自检、清洗、连接等）
- 进度条显示区域
- 紧急停止按钮（红色）

### 7.5 呼吸机界面设计

| 控件 | 类型 | 功能 |
|------|------|------|
| comboBox_ventilationMode | QComboBox | 通气模式选择 |
| doubleSpinBox_tidalVolume | QDoubleSpinBox | 潮气量 |
| doubleSpinBox_leakageVolume | QDoubleSpinBox | 漏气量 |
| doubleSpinBox_minuteVentilation | QDoubleSpinBox | 每分钟通气量 |
| spinBox_respiratoryRate | QSpinBox | 呼吸频率 |
| doubleSpinBox_inspiratoryTime | QDoubleSpinBox | 吸气时间 |
| doubleSpinBox_riseTime | QDoubleSpinBox | 升压时间 |
| doubleSpinBox_inspiratoryPressure | QDoubleSpinBox | 吸气压力 |
| doubleSpinBox_expiratoryPressure | QDoubleSpinBox | 呼气压力 |
| spinBox_backupRate | QSpinBox | 备用频率 |
| doubleSpinBox_ieRatio | QDoubleSpinBox | 呼吸比例 |
| widget_light | Alarm_Light | 状态指示灯 |
| btn_lock | QPushButton | 锁定/解锁按钮 |

### 7.6 数据传输客户端界面设计

- 五个功能通道配置区域
- 串口选择器和连接按钮
- 传输按钮和状态指示灯
- 日志显示区域

## 8. 错误处理设计

### 8.1 串口错误处理

| 错误类型 | 处理方式 |
|----------|----------|
| 串口未打开 | 显示错误提示，检查串口配置 |
| 串口读取失败 | 重试读取，记录日志 |
| 数据格式错误 | 忽略错误数据，记录日志 |

### 8.2 数据边界检查

- 心电图数据访问前检查索引范围
- 串口数据解析前检查数据长度
- 参数值范围检查

### 8.3 异常处理

- 使用 try-catch 捕获异常
- 异常发生时显示错误提示
- 记录异常日志

## 9. 性能优化

### 9.1 数据处理优化

- 使用定时器控制数据更新频率
- 减少不必要的数据拷贝
- 使用高效的数据结构

### 9.2 绘图优化

- 使用 QWT 优化曲线绘制
- 限制数据点数量
- 使用缓存机制

### 9.3 内存优化

- 及时释放不再使用的对象
- 使用智能指针管理内存
- 避免内存泄漏

## 10. 扩展性设计

### 10.1 新增设备模块

- 继承 QDialog 实现新的设备对话框
- 实现串口数据接收和处理逻辑
- 在主对话框添加入口按钮

### 10.2 串口协议扩展

- 在 Transmission 端添加新的功能通道
- 实现数据模拟算法
- 在 NICU 端实现数据接收和处理

### 10.3 配置文件支持

- 将串口配置移至配置文件
- 支持参数范围配置
- 支持界面布局配置

---

## 11. 版本信息

| 项目 | 版本 | 说明 |
|------|------|------|
| Qt | 6.11.1 | 主框架版本 |
| QWT | 6.3.0 | 图表绘制库 |
| C++ | C++17 | 语言标准 |
| 构建工具 | qmake | Qt 项目构建工具 |

---

## 12. 相关文档

| 文档名称 | 描述 |
|----------|------|
| [README.md](../README.md) | 项目简介和快速开始指南 |
| [项目技术文档](project_documentation.md) | 详细技术文档，包含项目结构、模块实现、算法说明 |
| [开发计划](development_plan.md) | 项目开发计划、进度安排、资源需求 |
| [需求规格说明](requirements_specification.md) | 完整需求规格说明文档 |
| [软件测试报告](test_report.md) | 测试用例、缺陷记录、测试结论 |