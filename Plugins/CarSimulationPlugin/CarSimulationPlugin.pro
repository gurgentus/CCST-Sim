#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T10:29:16
#
#-------------------------------------------------

QT       += widgets gui opengl charts

TARGET = $$qtLibraryTarget(CarSimulationPlugin)

TEMPLATE = lib

DEFINES += CARSIMULATIONPLUGIN_LIBRARY
CONFIG       += plugin static

INCLUDEPATH  += ../../../MyOpenGL
DESTDIR       = ../../../MyOpenGL/Plugins


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
        src/CarSimulationPlugin.cpp \
        src/AdaptiveCar.cpp \
        src/Car.cpp

HEADERS += \
        src/CarSimulationPlugin.hpp \
        src/Adaptivecar.hpp \
        src/Car.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
