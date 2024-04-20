#include "socketmanager.h"

SocketManager::SocketManager() {}

SocketManager::~SocketManager()
{
    delete socket;
}

SocketManager &SocketManager::instance()
{
    static SocketManager sM;
    return sM;
}

void SocketManager::connectSocket()
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &SocketManager::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("127.0.0.1", 2323);
}

void SocketManager::sendMessage(message& msg)
{
    msg.setSender(indificatorUser);
    sendToServer(msg);
}

void SocketManager::sendPrivateMessage(privateMessage &msg, int indexRecipient)
{
    msg.setSender(indificatorUser);
    msg.setRecipient(users[indexRecipient]);
    sendToServer(msg);
}

void SocketManager::registerUser(authData &user)
{
    user.setTypeRegisterRequest();
    sendToServer(user);
}

void SocketManager::autorizationUser(const QString &email, const QString &password)
{
    authData user(email, password);
    user.setTypeAuthRequest();
    sendToServer(user);
}

void SocketManager::logout()
{
    emit socket->disconnected();
}

void SocketManager::sendToServer(const baseData &dataToSend)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out<<dataToSend.type()<<dataToSend;
    socket->write(data);
}

void SocketManager::slotReadyRead()
{
    QDataStream data = QDataStream(socket);
    data.setVersion(QDataStream::Qt_6_2);
    if(data.status() == QDataStream::Ok){
        qDebug()<<"read...";
        qint8 type;
        data>>type;
        if(type == DataType::MESSAGE)
            readMessage(data);
        else if(type == DataType::USERLISTRESPONSE)
            readUserList(data);
        else if(type == DataType::AUTHRESPONSE)
            readAuthAnswer(data);
        else if(type == DataType::REGISTERRESPONSE)
            readRegisterAnswer(data);
        else if(type == DataType::CONNECTION)
            readNewConnection(data);
        else if(type == DataType::DISCONNECTION)
            readDisconnection(data);
    }
    else{
        qDebug()<<"QDataStream error";
    }
}

void SocketManager::readUserList(QDataStream &data)
{
    users.clear();
    data>>users;
    emit userListReceived(users);
}

void SocketManager::readMessage(QDataStream &data)
{
    message msg;
    data>>msg;
    emit messageReceived(msg);
}

void SocketManager::readAuthAnswer(QDataStream &data)
{
    authAnswer answer;
    data>>answer;
    if(answer.isAnswer()){
        indificatorUser = answer.getUser();
        emit userAuthenticated(indificatorUser.getName());
        userListRequest request;
        sendToServer(request);
    }
    else
        emit userAuthenticationFailed();
}

void SocketManager::readRegisterAnswer(QDataStream &data)
{
    authAnswer answer;
    data>>answer;
    if(answer.isAnswer())
        emit userRegistration();
    else
        emit userRegistrationFailed();
}

void SocketManager::readNewConnection(QDataStream &data)
{
    userInfo user;
    data>>user;
    users.push_back(user);
    emit newConnection(user);
}

void SocketManager::readDisconnection(QDataStream &data)
{
    userInfo user;
    data>>user;
    users.remove(user);
    emit disconnection(users);
}
