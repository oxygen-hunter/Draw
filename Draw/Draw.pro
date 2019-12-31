#-------------------------------------------------
#
# Project created by QtCreator 2019-10-21T11:16:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Draw
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Line.cpp \
    Primitive.cpp \
    Polygon.cpp \
    Ellipse.cpp \
    Curve.cpp \
    Painter.cpp

HEADERS += \
        mainwindow.h \
    Line.h \
    Primitive.h \
    Polygon.h \
    Ellipse.h \
    Curve.h \
    Painter.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    icons.qrc
