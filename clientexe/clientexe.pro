QT += core
QT -= gui

CONFIG += c++11

TARGET = exe
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test_nomanager.cpp

HEADERS += \
    test_nomanager.h
