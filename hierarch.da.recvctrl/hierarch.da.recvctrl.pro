QT += core gui widgets

TARGET = hierarch_da_recvctrl
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

FORMS += RecvWidget.ui

HEADERS += \
    ../plugindepends/IDAWidget.h \
    qpluginactivator.h \
    recvwidget.h

SOURCES += \
    qpluginactivator.cpp \
    recvwidget.cpp

RESOURCES += \
    resource.qrc
