#ifndef USERLISTREQUEST_H
#define USERLISTREQUEST_H
#include "basedata.h"

class userListRequest:public baseData
{
public:
    userListRequest();

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;
};

#endif // USERLISTREQUEST_H
