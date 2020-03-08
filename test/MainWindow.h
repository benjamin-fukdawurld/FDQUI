#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <FD3D/Utils/Transform.h>

#include <FDQUI/VectorModel.h>
#include <FDQUI/TransformModel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    protected:
        glm::vec4 m_vec;
        FD3D::Transform m_transform;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};

#endif // MAINWINDOW_H
