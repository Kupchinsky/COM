QT += core
QT -= gui

CONFIG += c++11

TARGET = exe
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../serverdll/component_i.c

HEADERS += \
    result_checker.h

LIBS += -luuid -loleaut32 -lole32
