#ifndef SERVER_H
#define SERVER_H
#include "databasemanagerauth.h"
#include "..\data\basedata.h"
#include "..\data\authData.h"
#include "..\data\message.h"
#include "..\data\userlist.h"
#include "..\data\privatemessage.h"
#include "..\data\authanswer.h"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QTime"
#include "QMap"


class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
private:
    void registerUser(const authData& user);
    void loginUser(const authData& user);
    void sendAuthAnswerToClient(bool isLogin, userInfo user);
    void sendRegisterAnswerToClient(bool isLogin);

    void sendMessageToClient(const message& msg);
    void sendPrivateMessage(const privateMessage& msg);

    void sendToClientListClients();

    void sendConnectionStatus(userInfo user, bool isConnection);

    void processAction(QDataStream& data);
    void write(QTcpSocket* socket, const baseData& dataFrom);
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void onClientDisconnection();
private:
    // QVector<QTcpSocket*> sockets;
    QMap<userInfo, QTcpSocket*> clients;
    // userList users;
    QByteArray data;
    QTcpSocket* socket;
};

#endif // SERVER_H
