#include "userinfo.h"


userInfo::userInfo(const qint64 &id, const QString &name, const QString &email):name(name), email(email), id(id)
{}

QDataStream &userInfo::toStream(QDataStream &data) const
{
    data<<id<<name<<email;
    return data;
}

QDataStream &userInfo::fromStream(QDataStream &data)
{
    data>>id>>name>>email;
    return data;
}

void userInfo::setUserName(const QString &name)
{
    this->name = name;
}

void userInfo::setUserEmail(const QString &email)
{
    this->email = email;
}

void userInfo::setuserId(const qint64 &id)
{
    this->id = id;
}

void userInfo::setConnection()
{
    dataType = DataType::CONNECTION;
}

void userInfo::setDisconnection()
{
    dataType = DataType::DISCONNECTION;
}

bool userInfo::operator<(const userInfo &right) const
{
    return this->email<right.email;
}

bool userInfo::operator==(const userInfo &right) const
{
    return this->email == right.getEmail() && this->name == right.getName();
}

DataType userInfo::type() const
{
    return dataType;
}
