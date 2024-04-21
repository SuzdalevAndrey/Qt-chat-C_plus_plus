#ifndef dataBaseManagerAuth_H
#define dataBaseManagerAuth_H
#include <QtSql>
#include <QDebug>
#include "..\data\userinfo.h"

class DataBaseManagerAuth
{
private:
    DataBaseManagerAuth();
    ~DataBaseManagerAuth();
    DataBaseManagerAuth(const DataBaseManagerAuth&) = delete;
    DataBaseManagerAuth& operator=(const DataBaseManagerAuth&) = delete;

    QSqlDatabase db;
public:
    userInfo getUserByEmail(const QString& email);
    bool registerUser(const QString& userName, const QString& userEmail, const QString& userPassword);
    bool userExists(const QString& email);
    bool authenticateUser(const QString& email, const QString& password);
    static DataBaseManagerAuth& instance();
};

#endif // dataBaseManagerAuth_H
