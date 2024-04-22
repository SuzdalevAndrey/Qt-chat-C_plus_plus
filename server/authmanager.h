#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "qobject.h"
#include "../data/authdata.h"
#include "../data/authanswer.h"
#include "../data/userinfo.h"
#include "databasemanagerauth.h"
#include "clientmanager.h"

class AuthManager:public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

signals:
    void userRegistered(bool success);
    void userLoggedIn(bool success, const userInfo& user);

public slots:
    void registerUser(const authData& user);
    void loginUser(const authData& user);
};

#endif // AUTHMANAGER_H
