#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T11:29:04
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

CONFIG += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pal_game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        controller.cpp \
    gameobject.cpp \
    image.cpp \
    life.cpp \
    bullet.cpp \
    role.cpp \
    enemy.cpp \
    health.cpp \
    goods.cpp \
    explode.cpp

HEADERS  += controller.h \
    gameobject.h \
    common.h \
    image.h \
    life.h \
    bullet.h \
    role.h \
    enemy.h \
    health.h \
    goods.h \
    explode.h

FORMS    += pal_game.ui

RESOURCES += \
    resource.qrc
