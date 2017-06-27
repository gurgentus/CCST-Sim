#ifndef SIMULATION_H
#define SIMULATION_H

#include "MainViewWidget.hpp"

#include "Common/Textures.hpp"
#include "Common/Control.hpp"

#include <QOpenGLWidget>

#include "SimulationInterface.hpp"

/* This is a parent class from which all simulations are derived.
 * Simulation object stores the shader program used in OpenGL rendering,
 * as well as textures used for the simulation.
 * The class also defined virtual methods that must be implemented by
 * inheriting classes.
 */
class Simulation : public MainViewWidget
{
public:
    explicit Simulation();
    // Shader and textures
    QOpenGLShaderProgram shader;
    Textures textures_;

    SimulationInterface* p_sim;

    // GUI Elements
    // Instructions label
    QLabel* instructions = new QLabel("Change text to include instructions");
    // Two simulation buttons
    QPushButton* p_sim_button1;
    QPushButton* p_sim_button2;

    // Pointer to the control and output panels
    QVBoxLayout* control_layout_;
    QVBoxLayout* output_layout_;

    // By default the GUI provides buttons for running two versions of the simulation
    // This specifies which version is currently being run
    int currentSim = 0;

    // Simulation speed control
    Control* speedControl_;

    void SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout* output_layout);

    // Virtual methods that need to be implemented for custom simulations
    void InitializeObjects(QPushButton* button1, QPushButton* button2);
    void InitializeObjects(QOpenGLShaderProgram* shader, Textures *textures_);

    double getSim_speed() const;
    void setSim_speed(double value);

    // Standard OpenGL methods
    void initializeGL();
    void paintGL();

protected Q_SLOTS:
    // Standard OpenGL methods
    void update();
    double sim_speed_ = 1;

};

#endif // SIMULATION_H
