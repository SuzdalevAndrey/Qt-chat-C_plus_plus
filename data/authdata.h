#ifndef authData_H
#define authData_H

#include "basedata.h"
#include <QString>

class authData : public baseData
{
public:
    authData();
    authData(const QString& name, const QString& email, const QString& password);
    authData(const QString& email, const QString& password);

    virtual QDataStream& toStream(QDataStream& data) const override;
    virtual QDataStream& fromStream(QDataStream& data) override;
    virtual DataType type()const override {return dataType;}

    void setUserName(const QString& name){this->name = name;}
    void setUserEmail(const QString& email){this->email = email;}
    void setUserPassword(const QString& password){this->password = password;}
    void setTypeAuthRequest() { dataType = DataType::AUTHREQUEST; }
    void setTypeRegisterRequest() { dataType = DataType::REGISTERREQUEST; }

    QString getName()const{return name;}
    QString getEmail()const{return email;}
    QString getPassword()const{return password;}

private:
    QString name;
    QString email;
    QString password;
    DataType dataType;
};

#endif // authData_H
