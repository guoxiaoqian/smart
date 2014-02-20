#-------------------------------------------------
#
# Project created by QtCreator 2014-02-10T12:15:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Viewer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MainView.cpp \
    generator.cpp \
    Config.cpp

HEADERS  += MainWindow.h \
    MainView.h \
    generator.h \
    struct.h \
    rand.h \
    Config.h

FORMS    += MainWindow.ui

OTHER_FILES +=
