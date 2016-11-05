#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T15:58:13
#
#-------------------------------------------------

QT       -= gui

TARGET = serverdll
TEMPLATE = lib

DEFINES += SERVERDLL_LIBRARY

SOURCES += serverdll.cpp \
    component1impl.cpp \
    component2impl.cpp \
    ../localregistry.cpp

HEADERS += serverdll.h\
        serverdll_global.h \
    component1.h \
    component2.h \
    component1impl.h \
    component2impl.h \
    ../localregistry.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

Release:QMAKE_LINK = dlltool -e release/exports.o --kill-at release/serverdll.o && g++
Debug:QMAKE_LINK = dlltool -e debug/exports.o --kill-at debug/serverdll.o && g++

Release:LIBS += release/exports.o
Debug:LIBS += debug/exports.o
