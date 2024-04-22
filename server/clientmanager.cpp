#include "clientmanager.h"


ClientManager::ClientManager()
{}

ClientManager::~ClientManager()
{}

void ClientManager::addClient(const userInfo &user, QTcpSocket *socket)
{
    clients.insert(user,socket);
}

void ClientManager::removeClient(const userInfo &user)
{
    clients.remove(user);
}

void ClientManager::writeAllClients(const baseData &dataFrom)
{
    for(auto& socket : clients.values())
        write(socket, dataFrom);
}

void ClientManager::writeOneClient(const userInfo &user, const baseData &dataFrom)
{
    if (clients.contains(user)) {
        write(clients[user], dataFrom);
    }
}

void ClientManager::writeListClient()
{
    userList users;
    for(auto user : clients.keys()){
        users.push_back(user);
    }
    for(auto socket : clients.values()){
        write(socket, users);
    }
}

ClientManager &ClientManager::instance()
{
    static ClientManager clientManager;
    return clientManager;
}

void ClientManager::writeLastClient(const baseData &dataFrom)
{
    if(lastSocket){
        if(dataFrom.type() == DataType::AUTHRESPONSE){
            const authAnswer *answer = dynamic_cast<const authAnswer*>(&dataFrom);
            if(answer && answer->isAnswer())
                clients.insert(answer->getUser(), lastSocket);
        }
        write(lastSocket, dataFrom);
    }
}

void ClientManager::setLastSocket(QTcpSocket *socket)
{
    lastSocket = socket;
}

void ClientManager::write(QTcpSocket *socket, const baseData &dataFrom)
{
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<dataFrom.type()<<dataFrom;
    socket->write(data);
}

userInfo ClientManager::getUserInfoBySocket(QTcpSocket* socket)
{
    return clients.key(socket);
}

void ClientManager::onClientDisconnection(QTcpSocket *disconnectionSocket)
{
    userInfo client = getUserInfoBySocket(disconnectionSocket);
    removeClient(client);
    client.setDisconnection();
    writeAllClients(client);
}
