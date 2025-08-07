QT += core gui widgets

TARGET = hierarch_da_datashow
TEMPLATE = lib
CONFIG += plugin

include($$PWD/../plugindepends/Plugindepends.pri)

HEADERS += \
    ../plugindepends/IDADataShowFactory.h \
    IDADataShowCtrl.h \
    dadatashowfactory.h \
    qdaviewshow.h \
    qpluginactivator.h

SOURCES += \
    dadatashowfactory.cpp \
    qdaviewshow.cpp \
    qpluginactivator.cpp

RESOURCES += \
    resource.qrc
