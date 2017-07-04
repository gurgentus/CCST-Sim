#include "Simulation.hpp"

Simulation::Simulation()
    : shader()
    , textures_()
{
    setFocusPolicy( Qt::StrongFocus );
}

void Simulation::InitializeObjects(QPushButton* button1, QPushButton *button2)
{
    p_sim_button1 = button1;
    p_sim_button2 = button2;
    InitializeObjects(&shader, &textures_);
}

void Simulation::InitializeObjects(QOpenGLShaderProgram* shader, Textures* textures)
{
    MainViewWidget::InitializeObjects(shader, textures);
    setFocusPolicy( Qt::StrongFocus );
}

void Simulation::initializeGL()
{
    MainViewWidget::initializeGL();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void Simulation::paintGL()
{
    MainViewWidget::paintGL();
    if (p_sim)
    {
        p_sim->RenderGraphics();
    }
}

void Simulation::update()
{
    MainViewWidget::update();
}

void Simulation::SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout *output_layout)
{
   control_layout_ = control_layout;
   output_layout_ = output_layout;
}

double Simulation::getSim_speed() const
{
    return sim_speed_;
}

void Simulation::setSim_speed(double value)
{
    sim_speed_ = value;
}

