#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T13:44:50
#
#-------------------------------------------------

QT       -= gui

TARGET = serverdll-extend
TEMPLATE = lib

DEFINES += SERVERDLLEXTEND_LIBRARY

SOURCES += serverdllextend.cpp \
    component_i.c \
    compoinentdispimpl.cpp \
    componentfactory.cpp \
    componentimpl.cpp

HEADERS += serverdllextend.h\
        serverdll-extend_global.h \
    component.h \
    componentfactory.h \
    componentimpl.h

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
