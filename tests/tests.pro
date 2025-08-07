QT += core gui widgets testlib

TARGET = tst_allplugins
TEMPLATE = app
CONFIG += testcase

include($$PWD/../plugindepends/Plugindepends.pri)

SOURCES += \
    tst_allplugins.cpp

HEADERS += \
    ../plugindepends/IDACIFD.h \
    ../plugindepends/IDADataShowFactory.h \
    ../plugindepends/IDAWidget.h


