#-------------------------------------------------
#
# Project created by QtCreator 2013-05-19T15:11:24
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BugzBunny
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signin.cpp \
    addproject.cpp \
    projectviewer.cpp

HEADERS  += mainwindow.h \
    signin.h \
    addproject.h \
    projectviewer.h

FORMS    += mainwindow.ui \
    signin.ui \
    addproject.ui \
    projectviewer.ui

RESOURCES += \
    res.qrc
