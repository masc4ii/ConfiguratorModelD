#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T16:57:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    messagecomposer.cpp

HEADERS  += mainwindow.h \
    messagecomposer.h

include($$PWD/../../QMidi.pri)
