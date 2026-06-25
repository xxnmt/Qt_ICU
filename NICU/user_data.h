#ifndef USER_DATA_H
#define USER_DATA_H
#include<QString>
class User_Data
{
private:
    QString User_Name;
    int User_Age;
public:
    User_Data();
    User_Data(QString name,int age);
    void setName(QString name);
    void setAge(int age);
    QString getName();
    int getAge();


};

#endif // USER_DATA_H
