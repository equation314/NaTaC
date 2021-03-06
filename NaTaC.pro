#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T12:32:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = NaTaC
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    mapwidget.cpp \
    tile.cpp \
    road.cpp \
    building.cpp \
    city.cpp \
    player.cpp \
    tradedialog.cpp \
    resourcetable.cpp \
    gameinfo.cpp

HEADERS  += mainwindow.h \
    mapwidget.h \
    tile.h \
    const.h \
    road.h \
    building.h \
    city.h \
    player.h \
    tradedialog.h \
    resourcetable.h \
    gameinfo.h

FORMS    += form/mainwindow.ui \
    form/tradedialog.ui

RESOURCES += \
    resource/res.qrc
