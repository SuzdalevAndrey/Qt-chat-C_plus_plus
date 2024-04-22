#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "qtcpsocket.h"
#include "../data/userinfo.h"
#include "../data/userlist.h"
#include "../data/authanswer.h"

class Server;

class ClientManager:public QObject
{
private:
    ClientManager();

    ~ClientManager();

    ClientManager(const ClientManager&) = delete;

    ClientManager& operator=(const ClientManager&) = delete;
public:
    void addClient(const userInfo& user, QTcpSocket* socket);

    void removeClient(const userInfo& user);

    void writeAllClients(const baseData& dataFrom);

    void writeOneClient(const userInfo& user, const baseData& dataFrom);

    void writeListClient();

    void writeLastClient(const baseData& dataFrom);

    static ClientManager& instance();

private:
    friend class Server;

    void setLastSocket(QTcpSocket* socket);

    void write(QTcpSocket* socket, const baseData& dataFrom);

    userInfo getUserInfoBySocket(QTcpSocket* socket);

    void onClientDisconnection(QTcpSocket* disconnectionSocket);

    QMap<userInfo, QTcpSocket*> clients;

    QTcpSocket* lastSocket;
};

#endif // CLIENTMANAGER_H
