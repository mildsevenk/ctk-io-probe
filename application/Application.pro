QT = core gui widgets

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include($$PWD/../plugindepends/Plugindepends.pri)

SOURCES += \
    main.cpp

HEADERS += \
    ../plugindepends/IDAMainWindow.h
