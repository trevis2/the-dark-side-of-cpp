#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T21:31:34
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = gl_graph
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cpp\
        glwin.cpp \
    mainwindow.cpp \
    modelobj.cpp

HEADERS  += glwin.h \
    mainwindow.h \
    modelobj.h

RESOURCES += \
    resources.qrc

#LIBS += -lGLU

FORMS += \
    mainwindow.ui

