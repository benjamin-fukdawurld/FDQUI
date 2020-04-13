#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <FDGL/BaseOpenGLWindow.h>
#include <FDGL/OpenGLShaderProgram.h>
#include <FDGL/OpenGLVertexArray.h>
#include <FDGL/OpenGLTexture.h>
#include <FDGL/OpenGLBuffer.h>

#include <QOpenGLWidget>


#include <FDCore/TimeManager.h>

#include <FD3D/SceneGraph/Scene.h>
#include <FD3D/SceneGraph/SceneLoader.h>


#include <functional>

namespace FDQUI
{
    class OpenGLWidget : public QOpenGLWidget, public FDGL::BaseOpenGLWindow
    {
        Q_OBJECT
        public:
            explicit OpenGLWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
            ~OpenGLWidget() override;

            bool create(int width, int height, const std::string &title) override;
            void destroy() override;
            bool isOpen() const override;

            void swapBuffer() const override;

            std::string getTitle() const override;
            void setTitle(const std::string &title) override;

            int getWidth() const override;
            void setWidth(int w) override;

            int getHeight() const override;
            void setHeight(int h) override;

        protected:
            void initializeGL() override;
            void paintGL() override;
            void resizeGL(int w, int h) override;

        signals:

        public slots:

};
}

#endif // OPENGLWINDOW_H
