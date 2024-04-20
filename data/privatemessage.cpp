#include "privatemessage.h"

privateMessage::privateMessage(userInfo sender, QString msg, userInfo recipient)
    : message(sender, msg), recipient(recipient){}

QDataStream &privateMessage::toStream(QDataStream &stream) const
{
    message::toStream(stream);
    stream << recipient;
    return stream;
}

QDataStream &privateMessage::fromStream(QDataStream &stream)
{
    message::fromStream(stream);
    stream>>recipient;
    return stream;
}

DataType privateMessage::type() const
{
    return DataType::PRIVATEMESSAGE;
}

void privateMessage::setRecipient(const userInfo &recipient)
{
    this->recipient = recipient;
}

userInfo privateMessage::getRecipient() const
{
    return recipient;
}
