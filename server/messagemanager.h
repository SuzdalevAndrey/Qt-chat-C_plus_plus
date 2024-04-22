#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "qobject.h"
#include "../data/message.h"
#include "../data/privatemessage.h"
#include "clientmanager.h"

class MessageManager: public QObject
{
    Q_OBJECT
public:
    explicit MessageManager(QObject *parent = nullptr);

public slots:
    void handleMessage(const message& msg);
    void handlePrivateMessage(const privateMessage& msg);
};

#endif // MESSAGEMANAGER_H
