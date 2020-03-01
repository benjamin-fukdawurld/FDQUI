#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <FDQUI/MatriceModel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    protected:
        glm::vec4 m_vec;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};

#endif // MAINWINDOW_H
