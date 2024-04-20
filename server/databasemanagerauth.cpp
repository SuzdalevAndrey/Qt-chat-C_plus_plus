#include "databasemanagerauth.h"

DataBaseManagerAuth::DataBaseManagerAuth() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) {
        qDebug() << "Failed to connect to database!";
    }
}

userInfo DataBaseManagerAuth::getUserByEmail(const QString &email)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return userInfo();
    }

    if (query.next()) {
        return userInfo(query.value(0).toInt(), query.value(1).toString(),query.value(2).toString());
    } else {
        qDebug() << "No user found with email:" << email;
        return userInfo();
    }
}

DataBaseManagerAuth::~DataBaseManagerAuth()
{
    db.close();
}

bool DataBaseManagerAuth::registerUser(const QString &userName, const QString &userEmail, const QString &userPassword)
{
    QSqlQuery query;

    query.prepare("INSERT INTO users (name, email, password) VALUES (:name, :email, :password)");
    query.bindValue(":name", userName);
    query.bindValue(":email", userEmail);
    query.bindValue(":password", userPassword);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DataBaseManagerAuth::userExists(const QString &email)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    return count > 0;
}

bool DataBaseManagerAuth::authenticateUser(const QString &email, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    return count > 0;
}

DataBaseManagerAuth &DataBaseManagerAuth::instance()
{
    static DataBaseManagerAuth dataBase;
    return dataBase;
}
