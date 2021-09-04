QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmainwidget.cpp \
    airlinesdetailwidget.cpp \
    airlinesitem.cpp \
    clickablelabel.cpp \
    main.cpp \
    loginwidget.cpp \
    mainwidget.cpp \
    mainwidgetminepart.cpp \
    modifypassworddialog.cpp \
    ordersdetailwidget.cpp \
    ordersitem.cpp \
    querywidget.cpp \
    welcomewidget.cpp

HEADERS += \
    adminmainwidget.h \
    airlinesdetailwidget.h \
    airlinesitem.h \
    clickablelabel.h \
    loginwidget.h \
    mainwidget.h \
    mainwidgetminepart.h \
    modifypassworddialog.h \
    ordersdetailwidget.h \
    ordersitem.h \
    querywidget.h \
    welcomewidget.h

FORMS += \
    adminmainwidget.ui \
    airlinesdetailwidget.ui \
    airlinesitem.ui \
    loginwidget.ui \
    mainwidget.ui \
    mainwidgetminepart.ui \
    modifypassworddialog.ui \
    ordersdetailwidget.ui \
    ordersitem.ui \
    querywidget.ui \
    welcomewidget.ui

TRANSLATIONS += \
    AirTicketingSystem_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
