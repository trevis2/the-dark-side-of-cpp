#-------------------------------------------------
#
# Project created by QtCreator 2012-09-19T21:31:34
#
#-------------------------------------------------

QT       += core gui opengl
TARGET = Model3DViewer
TEMPLATE = app
CONFIG += c++14

macx {
    CONFIG += warn_on
    QMAKE_CXXFLAGS_WARN_ON += -Wno-deprecated-copy
}


SOURCES += main.cpp\
        openglview.cpp \
    mainwindow.cpp \
    modelobj.cpp

HEADERS  += openglview.h \
    CustomSlider.h \
    mainwindow.h \
    modelobj.h

RESOURCES += \
    resources.qrc

#LIBS += -lGLU

FORMS += \
    mainwindow.ui

