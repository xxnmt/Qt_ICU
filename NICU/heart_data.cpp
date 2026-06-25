#include "heart_data.h"

#define MAX_DATA 310

Heart_Data::Heart_Data() {}

Heart_Data::Heart_Data(const Heart_Data &t)
{
    User_ChannelName=t.getChannelName();
    for(int i=0;i<t.getDataArr().size();i++){
        User_DataArr.append(t.getDataArr().at(i));
    }
}

QString Heart_Data::getChannelName() const
{
    return User_ChannelName;
}

QJsonArray Heart_Data::getDataArr() const
{
    return User_DataArr;
}

void Heart_Data::setChannelName(QString name)
{
    User_ChannelName=name;
}

void Heart_Data::setDataArr(QJsonArray dataArr)
{
    for(int i=0;i<dataArr.size();i++){
        User_DataArr.append(dataArr.at(i));
    }
}

void Heart_Data::addData(int data)
{
    if(User_DataArr.size()>=MAX_DATA)User_DataArr.pop_front();
    User_DataArr.append(data);
}
