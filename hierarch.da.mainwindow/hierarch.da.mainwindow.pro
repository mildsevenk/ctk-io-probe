QT += core gui widgets serialport

TARGET = hierarch_da_mainwindow
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

FORMS += MainWindow.ui

HEADERS += \
    ../plugindepends/IDACIFD.h \
    ../plugindepends/IDADataShowFactory.h \
    ../plugindepends/IDAMainWindow.h \
    ../plugindepends/IDAWidget.h \
    mainwindow.h \
    qpluginactivator.h

SOURCES += \
    mainwindow.cpp \
    qpluginactivator.cpp

RESOURCES += \
    resource.qrc

UI_DIR = .
