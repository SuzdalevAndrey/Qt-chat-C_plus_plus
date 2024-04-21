#ifndef CHATINFO_H
#define CHATINFO_H

#include "basedata.h"
#include "userlist.h"

class chatInfo : public baseData
{
public:
    chatInfo(const int& id = -1, const QString& name = "", const userList& participants = userList());

    virtual QDataStream &toStream(QDataStream &stream) const override;
    virtual QDataStream &fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    void setName(const QString& name);
    void setParticipants(const userList& participants);
    void setId(const int& id);
    void addParticipant(const userInfo& participant);

    userList getParticipants() const;
    QString getName() const;
    int getId() const;

    bool operator ==(const chatInfo& left) const;

private:
    QString name;
    userList participants;
    int id;
};

#endif // CHATINFO_H
