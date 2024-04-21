#include "chatlist.h"

chatList::chatList() {}

chatList::chatList(const QList<chatInfo> &chats):chats(chats)
{}

QDataStream &chatList::toStream(QDataStream &stream) const
{
    for(const auto& chat : chats){
        stream<<chat;
    }
    return stream;
}

QDataStream &chatList::fromStream(QDataStream &stream)
{
    while(!stream.atEnd()){
        chatInfo chat;
        stream>>chat;
        chats.push_back(chat);
    }
    return stream;
}

DataType chatList::type() const
{
    return dataType;
}

void chatList::setResponseType()
{
    dataType = DataType::CHATLISTRESPONSE;
}

void chatList::setRequestType()
{
    dataType = DataType::CHATLISTREQUEST;
}

void chatList::push_back(const chatInfo &chat)
{
    chats.push_back(chat);
}

void chatList::remove(const chatInfo &chat)
{
    for(int i = 0;i<chats.size();++i){
        if(chats[i] == chat){
            chats.remove(i);
            break;
        }
    }
}

void chatList::clear()
{
    chats.clear();
}

chatInfo &chatList::operator[](int index)
{
    if(index>=0 && index<chats.size())
        return chats[index];
    throw std::out_of_range("index chat no valid!");
}

const QList<chatInfo> &chatList::getChats() const
{
    return chats;
}
