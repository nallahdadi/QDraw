#-------------------------------------------------
#
# Project created by QtCreator 2012-02-29T02:49:52
#
#-------------------------------------------------
CONFIG	 += console debug
QT       += core gui

TARGET = QDraw
TEMPLATE = app


SOURCES += main.cpp\
        view.cpp \
    line.cpp \
    bezier.cpp \
    border.cpp \
    circle.cpp \
    polygan.cpp \
    rectangle.cpp \
    thumb.cpp \
    arc.cpp \
    arcdialog.cpp \
    textdialog.cpp \
    text.cpp \
    commands.cpp \
    itemeditdialog.cpp

HEADERS  += view.h \
    constants.h \
    line.h \
    bezier.h \
    border.h \
    circle.h \
    polygan.h \
    thumb.h \
    rectangle.h \
    arc.h \
    arcdialog.h \
    textdialog.h \
    text.h \
    commands.h \
    itemeditdialog.h

FORMS    += view.ui \
    arcDialog.ui \
    textdialog.ui \
    itemeditdialog.ui

RESOURCES += \
    QDraw.qrc
