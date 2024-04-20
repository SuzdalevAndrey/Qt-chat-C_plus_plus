#ifndef USERINFO_H
#define USERINFO_H

#include "basedata.h"
#include "QString"

class userInfo : public baseData
{
public:
    userInfo(const qint64& id = -1, const QString& name = "", const QString& email = "");

    virtual QDataStream& toStream(QDataStream& data) const override;
    virtual QDataStream& fromStream(QDataStream& data) override;

    virtual DataType type()const override;

    void setUserName(const QString& name);
    void setUserEmail(const QString& email);
    void setuserId(const qint64& id);
    void setConnection();
    void setDisconnection();

    QString getName()const{return name;}
    QString getEmail()const{return email;}
    qint64 getId()const{return id;}

    bool operator<(const userInfo& right) const;
    bool operator==(const userInfo& right) const;

private:
    QString name;
    QString email;
    qint64 id;
    DataType dataType;
};

#endif // USERINFO_H
