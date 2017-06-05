#ifndef CARSIMULATION_H
#define CARSIMULATION_H

#include "simulation.h"

#include <objects/terrain.h>
#include <objects/road.h>
#include <objects/car.h>
#include <objects/adaptivecar.h>


class CarSimulation : public Simulation
{
public:
    CarSimulation();

    // 3D objects
    Terrain terrain_;
    Road road_;
    Car lead_car_;
    AdaptiveCar car_;

    using Simulation::InitializeObjects;
    void InitializeObjects(QVBoxLayout *layout, QVBoxLayout *control_layout, QOpenGLShaderProgram* shader,
                           Textures *textures_);
    void InitializeObjects(QVBoxLayout* info_layout);

    // OpenGL functions
    void initializeGL();
    void paintGL();

    // Simulation logic functions
    void StartSimulation1();
    void StartSimulation2();
    void UpdateState(double dt);

protected Q_SLOTS:
    void update();

};

#endif // CARSIMULATION_H
