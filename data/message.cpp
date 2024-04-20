#include "message.h"

message::message(userInfo sender, QString message):sender(sender), messageSender(message) {}

QDataStream &message::toStream(QDataStream &stream) const
{
    stream<<sender<<messageSender;
    return stream;
}

QDataStream &message::fromStream(QDataStream &stream)
{
    stream>>sender>>messageSender;
    return stream;
}

DataType message::type() const
{
    return DataType::MESSAGE;
}

void message::setSender(const userInfo &sender)
{
    this->sender = sender;
}

void message::setMessage(const QString& message)
{
    messageSender = message;
}

userInfo message::getSender() const
{
    return sender;
}

QString message::getMessage() const
{
    return messageSender;
}
