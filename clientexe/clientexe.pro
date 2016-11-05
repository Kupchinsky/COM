QT += core
QT -= gui

CONFIG += c++11

TARGET = exe
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test_nomanager.cpp \
    test_manager.cpp

HEADERS += \
    test_nomanager.h \
    result_checker.h \
    test_manager.h
