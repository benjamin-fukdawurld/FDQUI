#include <FDQUI/GUI/OpenGLApplication.h>

#include <qlogging.h>

#include <QOpenGLContext>
#include <QOpenGLWidget>

FDQUI::OpenGLApplication::OpenGLApplication(int &argc, char **argv) :
    QApplication(argc, argv),
    FDGL::BaseOpenGLContext()
{}

FDQUI::OpenGLApplication::~OpenGLApplication()
{
    if(!quit())
        qFatal("Failed to quit OpenGLApplication");
}
bool FDQUI::OpenGLApplication::init()
{
    return true;
}

bool FDQUI::OpenGLApplication::quit()
{
    return true;
}

void FDQUI::OpenGLApplication::setCurrentContext(FDGL::BaseOpenGLWindow &window)
{
    reinterpret_cast<QOpenGLWidget&>(window).makeCurrent();
}

FDGL::BaseOpenGLContext::GetProcAddressFunc FDQUI::OpenGLApplication::getProcAddressFunc()
{
    return [](const char *name){
        return reinterpret_cast<void*>(QOpenGLContext::currentContext()->getProcAddress(name));
    };
}
