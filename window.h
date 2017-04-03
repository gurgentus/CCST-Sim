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

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    //QVBoxLayout* getControlLayout();
public Q_SLOTS:
    void updateState();
    void handleButton();
private:
    Ui::Window *ui;
    QTimer* timer;
    double simTime = 0;

    // GUI Elements
    MainViewWidget myOpenGLWidget;
    QVBoxLayout* rightLayout;
    QPushButton* m_button;

    // Initialize shader program, textures and 3D objects
    QOpenGLShaderProgram shader;
    Textures textures;
    Terrain g_Terrain;
    Road road;
    Car leadCar;
    Car car;

    constexpr static const float pi = 3.1415926535897932384626433832795f;
    constexpr static const float _2pi = 2.0f * pi;
};

#endif // WINDOW_H
