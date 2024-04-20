#ifndef USERLIST_H
#define USERLIST_H

#include "basedata.h"
#include "userinfo.h"
#include "qlist.h"

class userList : public baseData
{
public:
    userList();
    userList(const QList<userInfo> &users);

    virtual QDataStream &toStream(QDataStream &stream) const override;
    virtual QDataStream &fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    void push_back(const userInfo& user);
    void remove(const userInfo& user);
    void clear();
    userInfo& operator[](int index);

    const QList<userInfo>& getUsers()const;
private:
    QList<userInfo> users;
};

#endif // USERLIST_H
