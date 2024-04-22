#include "authmanager.h"

AuthManager::AuthManager(QObject *parent):QObject(parent){}

void AuthManager::registerUser(const authData &user)
{
    bool isRegistered = false;
    if(!DataBaseManagerAuth::instance().userExists(user.getEmail())){
        DataBaseManagerAuth::instance().registerUser(user.getName(), user.getEmail(), user.getPassword());
        isRegistered = true;
    }
    authAnswer answer;
    answer.setTypeRegisterAnswer();
    answer.setAnswer(isRegistered);
    ClientManager::instance().writeLastClient(answer);
}

void AuthManager::loginUser(const authData &user)
{
    bool isLogin = false;
    userInfo userLogin;
    if(DataBaseManagerAuth::instance().authenticateUser(user.getEmail(), user.getPassword())){
        userLogin = DataBaseManagerAuth::instance().getUserByEmail(user.getEmail());
        isLogin = true;
    }
    authAnswer answer;
    answer.setTypeAuthAnswer();
    answer.setAnswer(isLogin);
    answer.setUser(userLogin);
    ClientManager::instance().writeLastClient(answer);
}
