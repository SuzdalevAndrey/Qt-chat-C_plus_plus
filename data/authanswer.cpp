#include "authanswer.h"

authAnswer::authAnswer() {}

QDataStream &authAnswer::toStream(QDataStream &stream) const
{
    stream<<answer<<user;
    return stream;
}

QDataStream &authAnswer::fromStream(QDataStream &stream)
{
    stream>>answer>>user;
    return stream;
}

DataType authAnswer::type() const
{
    return dataType;
}

bool authAnswer::isAnswer() const
{
    return answer;
}

userInfo authAnswer::getUser() const
{
    return user;
}

void authAnswer::setAnswer(bool answer)
{
    this->answer = answer;
}

void authAnswer::setUser(userInfo user)
{
    this->user = user;
}

void authAnswer::setTypeAuthAnswer()
{
    dataType = DataType::AUTHRESPONSE;
}

void authAnswer::setTypeRegisterAnswer()
{
    dataType = DataType::REGISTERRESPONSE;
}
