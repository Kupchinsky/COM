#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T11:06:03
#
#-------------------------------------------------

QT       -= gui

TARGET = managerdll
TEMPLATE = lib

DEFINES += MANAGERDLL_LIBRARY

SOURCES += managerdll.cpp

HEADERS += managerdll.h\
        managerdll_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

Release:QMAKE_LINK = dlltool -e release/exports.o --kill-at release/managerdll.o && g++
Debug:QMAKE_LINK = dlltool -e debug/exports.o --kill-at debug/managerdll.o && g++

Release:LIBS += release/exports.o
Debug:LIBS += debug/exports.o
