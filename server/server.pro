QT = core
QT += network
QT += sql

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        databasemanagerauth.cpp \
        databasemanagerhistorychat.cpp \
        main.cpp \
        server.cpp \
        D:/data/authanswer.cpp \
        D:/data/basedata.cpp \
        D:/data/userlist.cpp \
        D:/data/authdata.cpp \
        D:/data/message.cpp \
        D:/data/userinfo.cpp \
        D:/data/privatemessage.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    databasemanagerauth.h \
    databasemanagerhistorychat.h \
    server.h \
    D:/data/authanswer.h \
    D:/data/basedata.h \
    D:/data/userlist.h \
    D:/data/authdata.h \
    D:/data/message.h \
    D:/data/userinfo.h \
    D:/data/privatemessage.h
