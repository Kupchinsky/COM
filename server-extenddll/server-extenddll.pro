#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T14:22:12
#
#-------------------------------------------------

QT       -= gui

TARGET = server-extenddll
TEMPLATE = lib

DEFINES += SERVEREXTENDDLL_LIBRARY

SOURCES += serverextenddll.cpp \
    component1eximpl.cpp

HEADERS += serverextenddll.h\
        server-extenddll_global.h \
    component1ex.h \
    component1eximpl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

Release:QMAKE_LINK = dlltool -e release/exports.o --kill-at release/serverextenddll.o && g++
Debug:QMAKE_LINK = dlltool -e debug/exports.o --kill-at debug/serverextenddll.o && g++

Release:LIBS += release/exports.o
Debug:LIBS += debug/exports.o
