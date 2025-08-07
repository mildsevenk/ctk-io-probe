QT += core gui widgets serialport

TARGET = hierarch_da_com
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

FORMS += ComWidget.ui

HEADERS += \
    ../plugindepends/IDACIFD.h \
    comwidget.h \
    qpluginactivator.h

SOURCES += \
    comwidget.cpp \
    qpluginactivator.cpp

RESOURCES += \
    resource.qrc

UI_DIR = .
