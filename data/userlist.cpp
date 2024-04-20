#include "userlist.h"

userList::userList() {}

userList::userList(const QList<userInfo> &users):users(users)
{}

QDataStream& userList::toStream(QDataStream &stream) const
{
    for (const auto &user : users) {
        stream << user;
    }
    return stream;
}

QDataStream& userList::fromStream(QDataStream &stream)
{
    while(!stream.atEnd()){
        userInfo user;
        stream>>user;
        users.push_back(user);
    }
    return stream;
}

DataType userList::type() const
{
    return DataType::USERLISTRESPONSE;
}

void userList::push_back(const userInfo &user)
{
    users.push_back(user);
}

void userList::remove(const userInfo &user)
{
    for(int i = 0;i<users.size();++i){
        if(users[i] == user){
            users.remove(i);
            break;
        }
    }
}

void userList::clear()
{
    users.clear();
}

userInfo &userList::operator[](int index)
{
    if(index>=0 && index<users.size())
        return users[index];
    throw std::out_of_range("Index no valid");
}

const QList<userInfo>& userList::getUsers() const
{
    return users;
}
