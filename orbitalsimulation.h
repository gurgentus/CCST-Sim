#ifndef ORBITALSIMULATION_H
#define ORBITALSIMULATION_H

#include "simulation.h"
#include "textures.h"
#include "objects/planet.h"
#include "nums/simulator.h"

class OrbitalSimulation : public Simulation
{
public:
    OrbitalSimulation();

    // 3D objects
    Planet earth_;
    Planet moon_;

    // For orbital mechanics simulation logic
    Simulator simulator;

    using Simulation::InitializeObjects;
    void InitializeObjects(QVBoxLayout *layout, QVBoxLayout *control_layout, QOpenGLShaderProgram* shader,
                           Textures *textures_, Planet *earth, Planet *moon);

    void setZRotation(int angle);
    void setYRotation(int angle);
    void setXRotation(int angle);

    // OpenGL logic
    void initializeGL();
    void paintGL();

    // simulation logic
    void UpdateState(double dt);
    void start_simulation1();
    void start_simulation2();

protected Q_SLOTS:
    void update();

private:
    void qNormalizeAngle(int &angle);
};

#endif // ORBITALSIMULATION_H

