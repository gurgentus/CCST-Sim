// main.cpp
#include <QApplication>
#include <QDesktopWidget>
#include <QtOpenGL>
#include <iostream>
#include <window.h>

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>
//#include <qwt_plot_grid.h>
//#include <qwt_symbol.h>
//#include <qwt_legend.h>

#include <QtCharts>

using namespace QtCharts;

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

//    QwtPlot plot;
//      plot.setTitle( "Plot Demo" );
//      plot.setCanvasBackground( Qt::white );
//      plot.setAxisScale( QwtPlot::yLeft, 0.0, 10.0);
//      plot.insertLegend( new QwtLegend() );

//      QwtPlotGrid *grid = new QwtPlotGrid();
//      grid->attach( &plot );

//      QwtPlotCurve *curve = new QwtPlotCurve();
//      curve->setTitle( "Pixel Count" );
//      curve->setPen( Qt::blue, 4 ),
//      curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

//      QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
//          QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
//      curve->setSymbol( symbol );

//      QPolygonF points;
//      points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
//          << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
//          << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );
//      curve->setSamples( points );

//      curve->attach( &plot );

//      plot.resize( 600, 400 );
//      plot.show();


    return app.exec();
}
