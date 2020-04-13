#include <MainWindow.h>
#include <QApplication>
#include <FDQUI/GUI/OpenGLApplication.h>
#include <FDQUI/GUI/Widget/OpenGLWidget.h>

int main(int argc, char *argv[])
{
    FDQUI::OpenGLApplication a(argc, argv);
    if(!a.init())
        return -1;

    MainWindow w;
    w.show();

    return a.exec();
}
