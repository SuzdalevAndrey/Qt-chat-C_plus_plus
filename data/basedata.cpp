#include "basedata.h"

QDataStream &operator << (QDataStream &stream, const baseData &data)
{
    return data.toStream(stream);
}

QDataStream &operator >> (QDataStream &stream, baseData &data)
{
    return data.fromStream(stream);
}
