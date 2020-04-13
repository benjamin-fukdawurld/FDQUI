#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <FD3D/Utils/Transform.h>
#include <FD3D/Light/Light.h>

#include <FDQUI/Model/VectorModel.h>
#include <FDQUI/Model/TransformModel.h>

#include <FDQUI/GUI/Widget/OpenGLWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    protected:
        FD3D::Transform m_transform;

        FDQUI::OpenGLWidget *m_glWindow;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        void prepareGLWidget();

        void prepareLeftDock();
};

#endif // MAINWINDOW_H
