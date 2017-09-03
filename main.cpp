// main.cpp
#include <QApplication>
#include <QDesktopWidget>
#include <QtOpenGL>
#include <iostream>
#include <Window.hpp>

#include <QtCharts>

using namespace QtCharts;

// Static plugins have to be listed here
Q_IMPORT_PLUGIN(SatelliteTrackingPlugin)
Q_IMPORT_PLUGIN(GroundStationSimulationPlugin)
Q_IMPORT_PLUGIN(CarSimulationPlugin)

int main(int argc, char *argv[])
{
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

    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    //window.setWindowTitle("GenELCSim");
    //window.resize(QSize(1000, 600));

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.showMaximized();
    else
        window.showMaximized();

    return app.exec();
}
