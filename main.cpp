// main.cpp
#include <QApplication>
#include <QDesktopWidget>
#include <QtOpenGL>
#include <iostream>
#include "window.h"

int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication app(argc, argv);

    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    QSurfaceFormat::setDefaultFormat(format);

    Window window;

    //window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    window.setWindowTitle("Simulator");

    //window.resize(QSize(1000, 600));

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.showMaximized();
    else
        window.showMaximized();

//    Window window2;
//    if (((float)widgetArea / (float)desktopArea) < 0.75f)
//        window2.show();
//    else
//        window2.showMaximized();

    return app.exec();
}
