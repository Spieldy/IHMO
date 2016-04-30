#-------------------------------------------------
#
# Project created by QtCreator 2016-03-18T17:57:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHMO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    advert_dialog.cpp \
    advert.cpp

HEADERS  += mainwindow.h \
    advert_dialog.h \
    advert.h

FORMS    += mainwindow.ui \
    advert.ui
