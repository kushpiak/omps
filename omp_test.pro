#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T09:49:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = omp_test
TEMPLATE = app


SOURCES += main.cpp\
        cbase.cpp \
        ccircle.cpp \
        clines.cpp \
        csquare.cpp \
        ctriangle.cpp \
        widget.cpp

HEADERS  += widget.h \
    cbase.h \
    ccircle.h \
    clines.h \
    csquare.h \
    ctriangle.h

FORMS    += widget.ui
