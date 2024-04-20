#include "server.h"

Server::Server() {
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug()<<"Start";
    }
    else{
        qDebug()<<"server fail";
    }
}

Server::~Server()
{
    delete socket;
}

void Server::registerUser(const authData &user)
{
    if(!DataBaseManagerAuth::instance().userExists(user.getEmail())){
        DataBaseManagerAuth::instance().registerUser(user.getName(), user.getEmail(), user.getPassword());
        sendRegisterAnswerToClient(true);
    }
    else{
        sendRegisterAnswerToClient(false);
    }
}

void Server::loginUser(const authData &user)
{
    if(DataBaseManagerAuth::instance().authenticateUser(user.getEmail(), user.getPassword())){
        qDebug()<<"Login is successfully";
        userInfo userLogin = DataBaseManagerAuth::instance().getUserByEmail(user.getEmail());
        clients.insert(userLogin, socket);
        sendAuthAnswerToClient(true, userLogin);
        // sendConnectionStatus(userLogin, true);
    }
    else{
        qDebug()<<"Login is not successfully";
        sendAuthAnswerToClient(false, userInfo());
    }
}

void Server::sendRegisterAnswerToClient(bool isLogin)
{
    authAnswer answer;
    answer.setTypeRegisterAnswer();
    answer.setAnswer(isLogin);
    write(socket, answer);
}

void Server::sendAuthAnswerToClient(bool isLogin, userInfo user)
{
    authAnswer answer;
    answer.setTypeAuthAnswer();
    answer.setAnswer(isLogin);
    answer.setUser(user);
    write(socket, answer);
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead,this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::onClientDisconnection);
    // connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    qDebug() << "ClientConnection " << socketDescriptor;
}

void Server::slotReadyRead(){
    socket = (QTcpSocket*)sender();
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
    auto disconnectedSocket = static_cast<QTcpSocket *>(sender());
    userInfo client = clients.key(disconnectedSocket);
    clients.remove(client);
    client.setDisconnection();
    for(auto socket : clients.values()){
        write(socket, client);
    }
}

void Server::sendMessageToClient(const message& msg){
    for(auto socket : clients.values()){
        write(socket, msg);
    }
}

void Server::sendPrivateMessage(const privateMessage& msg)
{
    message Message(msg.getSender(), msg.getMessage());
    for(auto client : clients.keys()){
        if(client.getEmail() == msg.getSender().getEmail() || client.getEmail() == msg.getRecipient().getEmail())
            write(clients[client], Message);
    }
}

void Server::sendToClientListClients()
{
    userList users;
    for(auto user : clients.keys()){
        users.push_back(user);
    }
    for(auto socket : clients.values()){
        write(socket, users);
    }
}

void Server::sendConnectionStatus(userInfo user, bool isConnection)
{
    isConnection?user.setConnection():user.setDisconnection();
    for(auto socket : clients.values()){
        write(socket, user);
    }
}

void Server::processAction(QDataStream& data)
{
    qint8 action;
    data>>action;
    if(action == DataType::MESSAGE){
        message msg;
        data>>msg;
        sendMessageToClient(msg);
    }
    else if(action == DataType::REGISTERREQUEST){
        authData user;
        data>>user;
        registerUser(user);
    }
    else if(action == DataType::AUTHREQUEST){
        authData user;
        data>>user;
        loginUser(user);
    }
    else if(action == DataType::USERLISTREQUEST){
        sendToClientListClients();
    }
    else if(action == DataType::PRIVATEMESSAGE){
        privateMessage message;
        data>>message;
        sendPrivateMessage(message);
    }
    // else if(action == DataType::CONNECTION){
    //     authData user;
    //     data>>user;
    //     users.push_back(user);
    //     qDebug()<<"Connection "<<user.getName()<<"\n";
    // }
}

void Server::write(QTcpSocket *socket, const baseData &dataFrom)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<dataFrom.type()<<dataFrom;
    socket->write(data);
}
