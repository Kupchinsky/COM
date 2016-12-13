#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T15:58:13
#
#-------------------------------------------------

QT       -= gui

TARGET = serverdll
TEMPLATE = lib

DEFINES += SERVERDLL_LIBRARY

SOURCES += \
    componentimpl.cpp \
    componentfactory.cpp \
    component_i.c \
    serverdll.cpp \
    compoinentdispimpl.cpp

HEADERS +=\
    componentimpl.h \
    component.h \
    componentfactory.h \
    serverdll.h \
    serverdll_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

Release:QMAKE_LINK = windres ../${QMAKE_TARGET}/rsrc.rc -o release/rsrc.o && dlltool -e release/exports.o --kill-at release/serverdll.o && g++
Debug:QMAKE_LINK = windres ../${QMAKE_TARGET}/rsrc.rc -o debug/rsrc.o && dlltool -e debug/exports.o --kill-at debug/serverdll.o && g++

Release:LIBS += release/exports.o
Release:LIBS += release/rsrc.o
Debug:LIBS += debug/exports.o
Debug:LIBS += debug/rsrc.o

LIBS += -luuid -loleaut32 -lole32 -lpsapi
