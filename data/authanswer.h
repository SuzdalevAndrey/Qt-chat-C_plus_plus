#ifndef AUTHANSWER_H
#define AUTHANSWER_H

#include "basedata.h"
#include "userinfo.h"

class authAnswer : public baseData
{
public:
    authAnswer();

    virtual QDataStream& toStream(QDataStream &stream) const override;
    virtual QDataStream& fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    bool isAnswer()const;
    userInfo getUser()const;

    void setAnswer(bool answer);
    void setUser(userInfo user);
    void setTypeAuthAnswer();
    void setTypeRegisterAnswer();

private:
    bool answer;
    userInfo user;
    DataType dataType;
};

#endif // AUTHANSWER_H
