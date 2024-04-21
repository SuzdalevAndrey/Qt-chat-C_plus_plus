#ifndef BASEDATA_H
#define BASEDATA_H

#include "qtypes.h"
#include "qdatastream.h"

enum DataType : qint8
{
    AUTHREQUEST,
    REGISTERREQUEST,
    AUTHRESPONSE,
    REGISTERRESPONSE,
    USERLISTRESPONSE,
    CONNECTION,
    DISCONNECTION,
    MESSAGE,
    USERLISTREQUEST,
    PRIVATEMESSAGE,
    USERINFO,
    CHATINFO,
    CHATLISTRESPONSE,
    CHATLISTREQUEST
};

class baseData
{
public:
    explicit baseData() = default;

    friend QDataStream &operator >> (QDataStream &stream, baseData &data);
    friend QDataStream &operator << (QDataStream &stream, const baseData &data);

    virtual QDataStream& toStream(QDataStream &stream) const = 0;
    virtual QDataStream& fromStream(QDataStream &stream) = 0;
    virtual DataType type() const  = 0;

    virtual ~baseData() = default;
};

QDataStream &operator >> (QDataStream &stream, baseData &data);
QDataStream &operator << (QDataStream &stream, const baseData &data);

#endif // BASEDATA_H
