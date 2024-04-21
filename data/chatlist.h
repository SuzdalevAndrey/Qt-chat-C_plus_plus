#ifndef CHATLIST_H
#define CHATLIST_H

#include "basedata.h"
#include "chatinfo.h"

class chatList : public baseData
{
public:
    chatList();
    chatList(const QList<chatInfo> &chats);

    virtual QDataStream &toStream(QDataStream &stream) const override;
    virtual QDataStream &fromStream(QDataStream &stream) override;
    virtual DataType type() const override;

    void setResponseType();
    void setRequestType();

    void push_back(const chatInfo& chat);
    void remove(const chatInfo& chat);
    void clear();
    chatInfo& operator[](int index);

    const QList<chatInfo>& getChats()const;
private:
    QList<chatInfo> chats;
    DataType dataType;
};

#endif // CHATLIST_H
