QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./CustomersWidgets/listuserswidget.cpp \
    chatwindow.cpp \
    createchatwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registrationwindow.cpp \
    socketmanager.cpp\
    ../data/authanswer.cpp \
    ../data/basedata.cpp \
    ../data/userlist.cpp \
    ../data/authdata.cpp \
    ../data/message.cpp \
    ../data/userlistrequest.cpp \
    ../data/userinfo.cpp \
    ../data/privatemessage.cpp

HEADERS += \
    ./CustomersWidgets/listuserswidget.h \
    chatwindow.h \
    createchatwindow.h \
    loginwindow.h \
    mainwindow.h \
    registrationwindow.h \
    socketmanager.h\
    ../data/authanswer.h \
    ../data/basedata.h \
    ../data/userlist.h \
    ../data/authdata.h \
    ../data/message.h \
    ../data/userlistrequest.h \
    ../data/userinfo.h \
    ../data/privatemessage.h

FORMS += \
    chatwindow.ui \
    createchatwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    registrationform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
