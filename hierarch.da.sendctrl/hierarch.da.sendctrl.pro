QT += core gui widgets

TARGET = hierarch_da_sendctrl
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

FORMS += SendWidget.ui

HEADERS += \
    ../plugindepends/IDAWidget.h \
    qpluginactivator.h \
    sendwidget.h

SOURCES += \
    qpluginactivator.cpp \
    sendwidget.cpp

RESOURCES += \
    resource.qrc

UI_DIR = .
