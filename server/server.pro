QT = core
QT += network
QT += sql

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        authmanager.cpp \
        databasemanagerauth.cpp \
        databasemanagerhistorychat.cpp \
        main.cpp \
        messagehandler.cpp \
        server.cpp \
        ../data/authanswer.cpp \
        ../data/basedata.cpp \
        ../data/userlist.cpp \
        ../data/authdata.cpp \
        ../data/message.cpp \
        ../data/userinfo.cpp \
        ../data/privatemessage.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    authmanager.h \
    databasemanagerauth.h \
    databasemanagerhistorychat.h \
    messagehandler.h \
    server.h \
    ../data/authanswer.h \
    ../data/basedata.h \
    ../data/userlist.h \
    ../data/authdata.h \
    ../data/message.h \
    ../data/userinfo.h \
    ../data/privatemessage.h
