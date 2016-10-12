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
    component2impl.cpp

HEADERS += serverdll.h\
        serverdll_global.h \
    unknown.h \
    component1.h \
    component2.h \
    component1impl.h \
    component2impl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
