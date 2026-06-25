#ifndef HEART_DATA_H
#define HEART_DATA_H

#include<QString>
#include<QJsonArray>

class Heart_Data
{
private:
    QString User_ChannelName;
    QJsonArray User_DataArr;
public:
    Heart_Data();
    Heart_Data(Heart_Data const &t);
    QString getChannelName()const;
    QJsonArray getDataArr()const;
    void setChannelName(QString name);
    void setDataArr(QJsonArray dataArr);
    void addData(int data);
};

#endif // HEART_DATA_H
