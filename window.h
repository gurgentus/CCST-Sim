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
#include "adaptivecar.h"
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
    void handleButton1();
    void handleButton2();
private:
    Ui::Window *ui;
    QTimer* timer;
    double simTime = 0;

    // GUI Elements
    MainViewWidget myOpenGLWidget;
    QVBoxLayout* right_layout;
    QVBoxLayout* bottom_right_layout;
    QVBoxLayout* fill_right_layout;
    QPushButton* m_button;
    QPushButton* m_button1;
    QPushButton* m_button2;
    int currentSim = 0;

    // Initialize shader program, textures and 3D objects
    QOpenGLShaderProgram shader;
    Textures textures;
    Terrain terrain_;
    Road road_;
    Car lead_car_;
    AdaptiveCar car_;

    constexpr static const float pi = 3.1415926535897932384626433832795f;
    constexpr static const float _2pi = 2.0f * pi;
};

#endif // WINDOW_H
