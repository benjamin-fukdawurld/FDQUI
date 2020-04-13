#ifndef OPENGLAPPLICATION_H
#define OPENGLAPPLICATION_H

#include <QApplication>

#include <glad/glad.h>

#include <FDGL/BaseOpenGLContext.h>

namespace FDQUI
{
    class OpenGLApplication;
}

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<FDQUI::OpenGLApplication *>(QCoreApplication::instance()))

namespace FDQUI
{
    class OpenGLApplication : public QApplication, public FDGL::BaseOpenGLContext
    {
        public:
            OpenGLApplication(int &argc, char **argv);
            ~OpenGLApplication() override;

            bool init() override;
            bool quit() override;
            void setCurrentContext(FDGL::BaseOpenGLWindow &window) override;

            static FDGL::BaseOpenGLContext::GetProcAddressFunc getProcAddressFunc();
    };
}

#endif // OPENGLAPPLICATION_H
