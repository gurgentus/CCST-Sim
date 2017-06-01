#ifndef SIMULATION_H
#define SIMULATION_H

#include "mainviewwidget.h"
#include "textures.h"
#include "control.h"

class Simulation : public MainViewWidget
{
public:
    explicit Simulation();
    // Shader and textures
    QOpenGLShaderProgram shader;
    Textures textures_;

    // GUI Elements
    // Instructions label
    QLabel* instructions = new QLabel("Change text to include instructions");

    int currentSim = 0;

    constexpr static const float pi = 3.1415926535897932384626433832795f;
    constexpr static const float _2pi = 2.0f * pi;

    virtual void InitializeObjects(QOpenGLShaderProgram* shader, Textures *textures_);
    virtual void InitializeObjects(QVBoxLayout* info_layout) = 0;
    virtual void UpdateState(double dt) = 0;


    virtual void start_simulation1() = 0;
    virtual void start_simulation2() = 0;

    void initializeGL();
    void paintGL();

    // simulation speed control
    Control* speedControl;

protected Q_SLOTS:
    void update();


};

#endif // SIMULATION_H
