#include "chatinfo.h"

chatInfo::chatInfo(const int& id, const QString& name, const userList &participants):name(name), participants(participants), id(id)
{}

QDataStream &chatInfo::toStream(QDataStream &stream) const
{
    stream<<id<<name<<participants;
    return stream;
}

QDataStream &chatInfo::fromStream(QDataStream &stream)
{
    stream>>id>>name>>participants;
    return stream;
}

DataType chatInfo::type() const
{
    return DataType::CHATINFO;
}

void chatInfo::setName(const QString &name)
{
    this->name = name;
}

void chatInfo::setParticipants(const userList &participants)
{
    this->participants = participants;
}

void chatInfo::setId(const int &id)
{
    this->id = id;
}

void chatInfo::addParticipant(const userInfo &participant)
{
    participants.push_back(participant);
}

userList chatInfo::getParticipants() const
{
    return participants;
}

QString chatInfo::getName() const
{
    return name;
}

int chatInfo::getId() const
{
    return id;
}

bool chatInfo::operator ==(const chatInfo &left) const
{
    return this->id == left.getId();
}
