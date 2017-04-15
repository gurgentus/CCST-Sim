#include "simulation.h"

Simulation::Simulation()
    : shader()
    , textures_()
{    
    setFocusPolicy( Qt::StrongFocus );
    right_layout = new QVBoxLayout;
    right_layout->addWidget(instructions);
}

void Simulation::InitializeObjects(QOpenGLShaderProgram* shader, Textures* textures)
{
    MainViewWidget::InitializeObjects(shader, textures);
}

void Simulation::initializeGL()
{
    MainViewWidget::initializeGL();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void Simulation::paintGL()
{
    MainViewWidget::paintGL();
}

void Simulation::update()
{
    MainViewWidget::update();
}
