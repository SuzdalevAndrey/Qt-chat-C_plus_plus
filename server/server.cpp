#include "server.h"

Server::Server() {
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug()<<"Start";
    }
    else{
        qDebug()<<"Server fail";
    }
}

Server::~Server()
{
    delete socket;
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead,this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::onClientDisconnection);
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
    ClientManager::instance().setLastSocket(socket);
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        qDebug()<<"read...";
        processAction(in);
    }
    else{
        qDebug()<<"QDataStream error";
    }
}

void Server::onClientDisconnection()
{
    auto disconnectedSocket = static_cast<QTcpSocket*>(sender());
    ClientManager::instance().onClientDisconnection(disconnectedSocket);
}

void Server::processAction(QDataStream& data)
{
    qint8 action;
    data>>action;
    if(action == DataType::MESSAGE){
        message msg;
        data>>msg;
        messageManager.handleMessage(msg);
    }
    else if(action == DataType::REGISTERREQUEST){
        authData user;
        data>>user;
        authManager.registerUser(user);
    }
    else if(action == DataType::AUTHREQUEST){
        authData user;
        data>>user;
        authManager.loginUser(user);
    }
    else if(action == DataType::USERLISTREQUEST){
        ClientManager::instance().writeListClient();
    }
    else if(action == DataType::PRIVATEMESSAGE){
        privateMessage message;
        data>>message;
        messageManager.handlePrivateMessage(message);
    }
}
