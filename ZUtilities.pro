#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T21:22:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZUtilities
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zstringutil.cpp \
    base64.cpp

HEADERS  += mainwindow.h \
    zstringutil.h \
    base64.h

FORMS    += mainwindow.ui
