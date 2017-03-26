// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include "mainviewwidget.h"
#include "terrain.h"
#include "road.h"
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
//protected:
//    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Window *ui;
    QVBoxLayout *rightLayout;
    MainViewWidget myOpenGLWidget;
    QOpenGLShaderProgram shader;
    Textures textures;
    Terrain g_Terrain;
    Road road;
};

#endif // WINDOW_H
