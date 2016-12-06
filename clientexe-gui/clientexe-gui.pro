#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T21:30:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clientexe-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../serverdll/component_i.c

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -luuid -loleaut32 -lole32
