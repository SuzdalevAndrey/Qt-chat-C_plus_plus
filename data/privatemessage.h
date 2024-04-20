#ifndef PRIVATEMESSAGE_H
#define PRIVATEMESSAGE_H

#include "message.h"

class privateMessage : public message
{
public:
    privateMessage(userInfo sender = userInfo(), QString msg = "", userInfo recipient = userInfo());

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    void setRecipient(const userInfo& recipient);

    userInfo getRecipient() const;
private:
    userInfo recipient;
};

#endif // PRIVATEMESSAGE_H
