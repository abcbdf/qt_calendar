#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T19:50:58
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
TRANSLATIONS+=cn.ts
TRANSLATIONS+=en.ts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    datedata.cpp \
    calendar.cpp \
    event.cpp \
    normalevent.cpp \
    label.cpp \
    login.cpp \
    super.cpp \
    shell.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    datedata.h \
    calendar.h \
    event.h \
    normalevent.h \
    label.h \
    login.h \
    super.h \
    shell.h

FORMS    += mainwindow.ui \
    dialog.ui \
    event.ui \
    normalevent.ui \
    login.ui \
    super.ui
