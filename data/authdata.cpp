#include "authData.h"

authData::authData():name(""),email(""),password("")
{}

authData::authData(const QString &name, const QString &email, const QString &password):name(name),email(email), password(password)
{}

authData::authData(const QString &email, const QString &password):name(""),email(email),password(password)
{}

QDataStream &authData::toStream(QDataStream &data) const
{
    data<<name<<email<<password;
    return data;
}

QDataStream &authData::fromStream(QDataStream &data)
{
    data>>name>>email>>password;
    return data;
}
