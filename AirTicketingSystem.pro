QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += gnu++11
#CONFIG += gnu++11
##CONFIG -= gnu++2a

CONFIG += fsd2f342fsdf
CONFIG += c++1y
#QMAKE_CXXFLAGS += -std=c++11


#QMAKE_CXXFLAGS += QMAKE_CXXFLAGS_CXX14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addflightwidget.cpp \
    adminmainwidget.cpp \
    airlinesdetailwidget.cpp \
    airlinesitem.cpp \
    buyaddpersondialog.cpp \
    cartitem.cpp \
    cartwidget.cpp \
    clickablelabel.cpp \
    flightsaveitem.cpp \
    flightsavewidget.cpp \
    main.cpp \
    loginwidget.cpp \
    mainwidget.cpp \
    mainwidgetminepart.cpp \
    modifypassworddialog.cpp \
    ordersdetailwidget.cpp \
    ordersitem.cpp \
    querywidget.cpp \
    welcomewidget.cpp \
    Person.cpp \
    Database.cpp \
    Admin.cpp \
    Buyer.cpp \
    Children_order.cpp \
    Mother_order.cpp \
    Order.cpp \
    Flight.cpp \
    Inquiry.cpp \
    File.cpp

HEADERS += \
    addflightwidget.h \
    adminmainwidget.h \
    airlinesdetailwidget.h \
    airlinesitem.h \
    buyaddpersondialog.h \
    cartitem.h \
    cartwidget.h \
    clickablelabel.h \
    flightsaveitem.h \
    flightsavewidget.h \
    loginwidget.h \
    mainwidget.h \
    mainwidgetminepart.h \
    modifypassworddialog.h \
    ordersdetailwidget.h \
    ordersitem.h \
    querywidget.h \
    welcomewidget.h \
    Person.h \
    Database.h \
    Admin.h \
    Buyer.h \
    Children_order.h \
    Mother_order.h \
    Order.h \
    Flight.h \
    Inquiry.h \
    File.h

FORMS += \
    addflightwidget.ui \
    adminmainwidget.ui \
    airlinesdetailwidget.ui \
    airlinesitem.ui \
    buyaddpersondialog.ui \
    cartitem.ui \
    cartwidget.ui \
    flightsaveitem.ui \
    flightsavewidget.ui \
    loginwidget.ui \
    mainwidget.ui \
    mainwidgetminepart.ui \
    modifypassworddialog.ui \
    ordersdetailwidget.ui \
    ordersitem.ui \
    querywidget.ui \
    welcomewidget.ui

INCLUDEPATH += include/ \
    include/mysql/

#LIBS += -Llib/ -llibmysql \
#    -Llib/ -llibprotobuf-lite \
#    -Llib/ -lmysqlclient \
#    -Llib/ -lmysqlharness_stdx \
#    -Llib/ -lmysqlharness_tls \
#    -Llib/ -lmysqlrouter_http \
#    -Llib/ -lmysqlrouter_http \
#    -Llib/ -lmysqlrouter_http \
#    -Llib/ -lmysqlrouter_http_auth_realm \
#    -Llib/ -lmysqlrouter_io_component \
#    -Llib/ -lmysqlrouter_lib

#LIBS += \
#    -L./lib/libmysql.lib \
#    -L./lib/libprotobuf-lite.lib \
#    -L./lib/mysqlclient.lib \
#    -L./lib/mysqlharness_stdx.lib \
#    -L./lib/mysqlharness_tls.lib \
#    -L./lib/mysqlrouter_http.lib \
#    -L./lib/mysqlrouter_http.lib \
#    -L./lib/mysqlrouter_http.lib \
#    -L./lib/mysqlrouter_http_auth_realm.lib \
#    -L./lib/mysqlrouter_io_component.lib \
#    -L./lib/mysqlrouter_lib.lib

LIBS += \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/libprotobuf-lite.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlclient.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlharness_stdx.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlharness_tls.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_http.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_http.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_http.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_http_auth_realm.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_io_component.lib' \
    'C:/Program Files/MySQL/MySQL Server 8.0/lib/mysqlrouter_lib.lib'

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
