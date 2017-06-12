#ifndef SIMULATION_H
#define SIMULATION_H

#include <mainviewwidget.h>
#include <common/textures.h>
#include <common/control.h>

/* This is a parent class from which all simulations are derived.
 * Simulation object stores the shader program used in OpenGL rendering,
 * as well as textures used for the simulation.
 * The class also defined virtual methdos that must be implemented by
 * inheriting classes.
 */
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

    // Pointer to the control and output panels
    QVBoxLayout* control_layout_;
    QVBoxLayout* output_layout_;

    // By default the GUI provides buttons for running two versions of the simulation
    // This specifies which version is currently being run
    int currentSim = 0;

    // Simulation speed control
    Control* speedControl_;

    void SetControlOutputPanel(QVBoxLayout* control_layout, QVBoxLayout* output_layout);

    // Constants used in simulations
    constexpr static const float pi = 3.1415926535897932384626433832795f;
    constexpr static const float _2pi = 2.0f * pi;

    // Virtual methods that need to be implemented for custom simulations
    virtual void InitializeObjects(QOpenGLShaderProgram* shader, Textures *textures_);
    virtual void InitializeObjects(QVBoxLayout* info_layout) = 0;
    virtual void UpdateState(double dt) = 0;
    virtual void StartSimulation1() = 0;
    virtual void StartSimulation2() = 0;

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
