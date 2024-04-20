QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        authanswer.cpp \
        authdata.cpp \
        basedata.cpp \
        main.cpp \
        message.cpp \
        privatemessage.cpp \
        userinfo.cpp \
        userlist.cpp \
        userlistrequest.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    authanswer.h \
    authdata.h \
    basedata.h \
    message.h \
    privatemessage.h \
    userinfo.h \
    userlist.h \
    userlistrequest.h
