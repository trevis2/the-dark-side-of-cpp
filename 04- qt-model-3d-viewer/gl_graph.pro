#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T21:31:34
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = gl_graph
TEMPLATE = app


SOURCES += main.cpp\
        glwin.cpp \
    mainwindow.cpp \
    modelobj.cpp

HEADERS  += glwin.h \
    mainwindow.h \
    modelobj.h

RESOURCES += \
    resources.qrc

FORMS += \
    mainwindow.ui