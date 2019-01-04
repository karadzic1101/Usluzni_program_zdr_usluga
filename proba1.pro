#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T14:48:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proba1
TEMPLATE = app

win32:RC_ICONS += picture.ico
QMAKE_LFLAGS += -static-libgcc

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    database.cpp \
    calendarform.cpp \
    izvestajform.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    database.h \
    calendarform.h \
    izvestajform.h

FORMS    += mainwindow.ui \
    dialog.ui \
    calendarform.ui \
    izvestajform.ui
