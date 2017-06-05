#ifndef ORBITALSIMULATION_H
#define ORBITALSIMULATION_H

#include <common/simulation.h>
#include <common/textures.h>
#include <objects/planet.h>
#include <nums/TwoBodySolver.h>

class OrbitalSimulation : public Simulation
{
public:
    OrbitalSimulation();

    // 3D objects
    vector<Planet*> planets;
    // Planet earth_;
    // Planet moon_;

    void AddPlanet(Planet& planet);
    using Simulation::InitializeObjects;
    void InitializeObjects(QVBoxLayout *layout, QVBoxLayout *control_layout, QOpenGLShaderProgram* shader,
                           Textures *textures_);
    void InitializeObjects(QVBoxLayout* info_layout);

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

