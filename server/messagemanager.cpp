#include "messagemanager.h"


MessageManager::MessageManager(QObject *parent):QObject(parent)
{}

void MessageManager::handleMessage(const message &msg)
{
    ClientManager::instance().writeAllClients(msg);
}

void MessageManager::handlePrivateMessage(const privateMessage &msg)
{
    message Message(msg.getSender(), msg.getMessage());
    ClientManager::instance().writeOneClient(msg.getSender(), Message);
    ClientManager::instance().writeOneClient(msg.getRecipient(), Message);
}
