#-------------------------------------------------
#
# Project created by QtCreator 2020-02-29T18:51:14
#
#-------------------------------------------------

QT += gui opengl

TARGET = FDQUI
TEMPLATE = lib

CONFIG += console c++17

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
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib
LIBS += -lFDCore -lFD3D -lFDCore -lFDGL -lglad
LIBS += -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lstdc++

INCLUDEPATH += include \
    ../FD3D/include \
    ../FDGL/include \
    ../FDCore/include \
    ../thirdparty/ \
    ../thirdparty/glm \
    ../thirdparty/glad/include \
    ../thirdparty/assimp/include \

SOURCES += \
    src/MatriceModel.cpp \
    src/StrategyModel.cpp \
    src/TransformDelegate.cpp \
    src/VectorModel.cpp \
    src/QuaternionModel.cpp \
    src/TransformModel.cpp \
    src/VertexModel.cpp \
    src/OpenGLApplication.cpp \
    src/LightModel.cpp \
    src/OpenGLWidget.cpp \
    src/VectorView.cpp \
    src/ColorModel.cpp \
    src/ColorWidget.cpp \
    src/VectorWidget.cpp \
    src/VectorDelegate.cpp

HEADERS += \
    include/FDQUI/Model/MatriceModel.h \
    include/FDQUI/Model/StrategyModel.h \
    include/FDQUI/Model/LightModel.h \
    include/FDQUI/Model/VectorModel.h \
    include/FDQUI/Model/QuaternionModel.h \
    include/FDQUI/Model/TransformModel.h \
    include/FDQUI/Model/VertexModel.h \
\
    include/FDQUI/GUI/OpenGLApplication.h \
\
    include/FDQUI/GUI/Widget/OpenGLWidget.h \
\
    include/FDQUI/GUI/View/TransformDelegate.h \
    include/FDQUI/GUI/View/VectorView.h \
    include/FDQUI/Model/ColorModel.h \
    include/FDQUI/GUI/Widget/ColorWidget.h \
    include/FDQUI/GUI/Widget/VectorWidget.h \
    include/FDQUI/GUI/View/VectorDelegate.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
