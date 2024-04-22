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
#include "authmanager.h"
#include "messagemanager.h"
#include "clientmanager.h"


class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
private:
    void processAction(QDataStream& data);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void onClientDisconnection();

private:
    QTcpSocket* socket;
    AuthManager authManager;
    MessageManager messageManager;
};

#endif // SERVER_H
