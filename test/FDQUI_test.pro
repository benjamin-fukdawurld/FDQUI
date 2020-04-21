#-------------------------------------------------
#
# Project created by QtCreator 2020-02-28T12:34:43
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FDQUI_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

DESTDIR = ../../build/bin
MAKEFILE = ../../build/makefiles/$${TARGET}
OBJECTS_DIR = ../../build/obj/$${TARGET}

LIBS += -L../../build/lib
LIBS += -L../../thirdparty/assimp/bin
LIBS +=  -lFDQUI -lFD3D -lFDCore -lassimp -lFDGL -lglad
LIBS += -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lstdc++

#LIBS += -lglad -lFDGL -lFDCore
#LIBS += -lglfw -lGL -lpthread -ldl -lX11 -lXrandr -lstdc++

INCLUDEPATH += \
    ../include \
    ../../thirdparty/glm \
    ../../FD3D/include \
    ../../FDGL/include \
    ../../FDCore/include \
    ../../thirdparty/glad/include \
    ../../thirdparty/assimp/include \

SOURCES += \
    MainWindow.cpp \
    main.cpp \

HEADERS += \
        MainWindow.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
