#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T09:56:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
#    myopenglwidget.cpp \
    transform3d.cpp \
    input.cpp \
    camera3D.cpp \
    control.cpp \
    cst/transferfunction.cpp \
    cst/cst.cpp \
    cst/complexnumber.cpp \
    cst/pfd.cpp \
    mainviewwidget.cpp \
    textures.cpp \
    nums/AbstractOdeSolver.cpp \
    nums/ForwardEulerSolver.cpp \
    nums/NumericalSolver.cpp \
    nums/RungeKuttaSolver.cpp \
    nums/simulator.cpp \
    output.cpp \
    carsimulation.cpp \
    orbitalsimulation.cpp \
    simulation.cpp \
    objects/car.cpp \
    objects/adaptivecar.cpp \
    objects/mesh.cpp \
    objects/road.cpp \
    objects/sbody.cpp \
    objects/planet.cpp \
    objects/terrain.cpp \
#    objects/part.cpp \
#    objects/wing.cpp \
#    objects/airplane.cpp
#    dynamiccontrol.cpp

HEADERS  += window.h \
#    myopenglwidget.h \
    vertex.h \
    transform3d.h \
    input.h \
    camera3D.h \
    control.h \
    cst/transferfunction.h \
    cst/cst.h \
    cst/complexnumber.h \
    cst/pfd.h \
    mainviewwidget.h \
    textures.h \
    nums/AbstractOdeSolver.hpp \
    nums/ForwardEulerSolver.hpp \
    nums/RungeKuttaSolver.hpp \
    nums/simulator.h \
    output.h \
    carsimulation.h \
    orbitalsimulation.h \
    simulation.h \
    objects/planet.h \
    objects/car.h \
    objects/adaptivecar.h \
    objects/road.h \
    objects/sbody.h \
    objects/mesh.h \
    objects/terrain.h \
#    objects/airplane.h \
#    objects/part.h \
#    objects/wing.h
#    dynamiccontrol.h

FORMS    += window.ui

DISTFILES += \
    SimpleFragmentShader.fragmentshader \
    SimpleVertexShader.vertexshader \
    shaders/simple.vert \
    shaders/simple.frag \
    shaders/texturediffuse.fsh \
    shaders/texturedDiffuse.frag \
    shaders/texturedDiffuse.vert \
    nums/hello-c-world \
    nums/hello-cpp-world \
    nums/data.txt \
    glm/CMakeLists.txt \
    nums/README.md \
    sample.py \
    Data/Terrain/terrain0-8bbp-257x257.raw \
    Data/Terrain/terrain0-16bbp-257x257.raw \
    Data/Textures/grass.jpg \
    Data/Textures/skydome4.jpg \
    Data/Textures/snow.jpg \
    Data/Textures/rock.png \
    Data/Objects/cube.obj

RESOURCES += \
    resources.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/release/ -lpython3.5m
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Applications/anaconda/lib/debug/ -lpython3.5m
else:unix: LIBS += -L$$PWD/../../../../Applications/anaconda/lib/ -lpython3.5m

INCLUDEPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m


#INCLUDEPATH += /usr/local/Cellar/boost/1.60.0_2/include/
#LIBS += -L/usr/local/Cellar/boost/1.60.0_2/lib/ -lboost_filesystem -lboost_system

DEPENDPATH += $$PWD/../../../../Applications/anaconda/include/python3.5m
CONFIG += no_keywords

QMAKE_MAC_SDK = macosx10.12
