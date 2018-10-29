#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T14:48:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proba1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp
#    zdrbaza.cpp

HEADERS  += mainwindow.h \
    dialog.h
#    zdrbaza.h

FORMS    += mainwindow.ui \
    dialog.ui
