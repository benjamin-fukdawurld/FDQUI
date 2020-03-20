#-------------------------------------------------
#
# Project created by QtCreator 2020-02-29T18:51:14
#
#-------------------------------------------------

QT += gui opengl

TARGET = FDQUI
TEMPLATE = lib

CONFIG += console c++17
#CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/.obj/$${TARGET}

LIBS += -L../build/lib
LIBS += -lFDCore -lFD3D -lFDCore

PRE_TARGETDEPS += \
#    ../../build/lib/libFD3D.a \
#    ../../build/lib/libFDCore.a \

DEPENDPATH += \
    ../../build/lib/

INCLUDEPATH += include \
    ../FD3D/include \
    ../FDCore/include \
    ../thirdparty/glm \

SOURCES += \
    src/MatriceModel.cpp \
    src/StrategyModel.cpp \
    src/TransformDelegate.cpp \
    src/VectorModel.cpp \
    src/QuaternionModel.cpp \
    src/TransformModel.cpp \
    src/VertexModel.cpp

HEADERS += \
    include/FDQUI/MatriceModel.h \
    include/FDQUI/StrategyModel.h \
    include/FDQUI/TransformDelegate.h \
    include/FDQUI/VectorModel.h \
    include/FDQUI/QuaternionModel.h \
    include/FDQUI/TransformModel.h \
    include/FDQUI/VertexModel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
