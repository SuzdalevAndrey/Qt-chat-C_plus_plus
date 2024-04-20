#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "qobject.h"
#include "qtcpsocket.h"
#include "D:\data\basedata.h"
#include "D:\data\authdata.h"
#include "D:\data\message.h"
#include "D:\data\userlist.h"
#include "D:\data\authanswer.h"
#include "D:\data\userlistrequest.h"
#include "D:\data\privatemessage.h"
#include "D:\data\userinfo.h"

class SocketManager: public QObject
{
    Q_OBJECT;

public:
    static SocketManager& instance();

signals:
    void userAuthenticated(const QString& name);
    void messageReceived(const message& message);
    void userListReceived(const userList& userList);
    void disconectionReceived();
    void userAuthenticationFailed();
    void userRegistration();
    void userRegistrationFailed();
    void newConnection(const userInfo& user);
    void disconnection(const userList &users);

public slots:
    void slotReadyRead();
    void connectSocket();
    void sendMessage(message& msg);
    void sendPrivateMessage(privateMessage& msg, int indexRecipient);
    void registerUser(authData& user);
    void autorizationUser(const QString &email, const QString &password);
    void logout();

private:
    SocketManager();
    ~SocketManager();
    SocketManager(const SocketManager&) = delete;
    SocketManager& operator=(const SocketManager&) = delete;

    void readUserList(QDataStream& data);
    void readMessage(QDataStream& data);
    void readAuthAnswer(QDataStream& data);
    void readRegisterAnswer(QDataStream& data);
    void readNewConnection(QDataStream& data);
    void readDisconnection(QDataStream& data);

    void sendToServer(const baseData& dataToSend);

    QTcpSocket *socket;
    QByteArray data;
    userInfo indificatorUser;
    userList users;
};

#endif // SOCKETMANAGER_H
