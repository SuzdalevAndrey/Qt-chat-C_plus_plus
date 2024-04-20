#include "userlistrequest.h"

userListRequest::userListRequest() {}

QDataStream &userListRequest::toStream(QDataStream &stream) const
{
    return stream;
}

QDataStream &userListRequest::fromStream(QDataStream &stream)
{
    return stream;
}

DataType userListRequest::type() const
{
    return DataType::USERLISTREQUEST;
}
