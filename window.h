// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include "mainviewwidget.h"
#include "terrain.h"
#include "road.h"
#include "car.h"
#include "textures.h"

//#define EARTH_TEXTURE 0
//#define MOON_TEXTURE 1
//#define GRASS_TEXTURE 2
//#define ROCK_TEXTURE 3

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    QVBoxLayout* getControlLayout();
public Q_SLOTS:
    void updateState();
    void handleButton();
private:
    Ui::Window *ui;
    QVBoxLayout *rightLayout;
    QPushButton* m_button;
    QTimer* timer;
    double simTime = 0;
    MainViewWidget myOpenGLWidget;
    QOpenGLShaderProgram shader;
    Textures textures;
    Terrain g_Terrain;
    Road road;
    Car car;
    //protected:
    //    void keyPressEvent(QKeyEvent *event);
};

#endif // WINDOW_H
