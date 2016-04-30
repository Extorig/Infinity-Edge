#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T13:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Infinity-Edge
TEMPLATE = app


SOURCES += main.cpp\
        infinityedge.cpp \
    fieldgenerator.cpp \
    field.cpp \
    fieldobject.cpp

HEADERS  += infinityedge.h \
    fieldobject.h \
    sides.h \
    fieldgenerator.h \
    field.h

FORMS    += infinityedge.ui

QMAKE_CXXFLAGS += -std=c++11
