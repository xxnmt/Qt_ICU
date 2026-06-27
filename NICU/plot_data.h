#ifndef PLOT_DATA_H
#define PLOT_DATA_H
#include <qwt_series_data.h>

class Plot_Data:public QwtSeriesData<QPointF>
{
public:

    Plot_Data();// 构造函数，初始化数据容器和参数
    size_t size() const; // 返回数据点的总数（QWT纯虚函数实现）
    QPointF sample(size_t i) const;// 返回第i个数据点，用于绘图（QWT纯虚函数实现）
    QRectF boundingRect() const; // 返回所有数据的边界矩形，用于优化绘图范围（QWT纯虚函数实现）
    void setParam(int sampleRate, double xWidth);// 设置采样参数：采样率(Hz)和X轴显示宽度(秒)
    void addBaseData(quint64 startTime, QVector<unsigned char> basedata);// 批量添加历史数据：起始时间戳(毫秒)和原始数据数组
    bool updateCurveData(unsigned char recvdata);// 实时更新曲线数据：接收一个字节的新数据，返回是否成功更新
    QwtInterval getXInterval();// 获取当前X轴的数据范围（最小值和最大值）
private:
    QVector<QPointF> m_value;// 存储所有数据点，x为时间(秒)，y为数据值
    QRectF m_boundingRect;// 缓存的数据边界矩形，避免重复计算
    int m_maxCount;// 最大存储数据点数（由采样率和显示宽度计算得出）
    double m_xWidth;// X轴显示的时间宽度（秒）
    int m_sampleRate;// 采样率（Hz），每秒采集的数据点数
    quint64 m_intervalTime;// 采样间隔时间（毫秒），由采样率计算得出
    quint64 m_intergrationTime;// 积分时间/累计时间（毫秒），用于时间相关计算
    QList<unsigned char> m_listPendingValue;// 待处理数据缓冲区，用于缓存未处理的数据
};

#endif // PLOT_DATA_H
