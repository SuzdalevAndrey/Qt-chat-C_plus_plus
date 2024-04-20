#ifndef MESSAGE_H
#define MESSAGE_H

#include "basedata.h"
#include "userinfo.h"
#include "qstring.h"

class message : public baseData
{
public:
    message(userInfo sender = userInfo(), QString message = "");

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    void setSender(const userInfo& sender);
    void setMessage(const QString& message);

    userInfo getSender()const;
    QString getMessage() const;
private:
    userInfo sender;
    QString messageSender;
};

#endif // MESSAGE_H
