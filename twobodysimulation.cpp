#include "twobodysimulation.h"

void TwoBodySimulation::InitializeSimulation()
{
    moon_.setP_simulator(&simulator);
    moon_.setR(1);
    moon_.setTranslation(QVector3D(10,10,0));
    moon_.local_to_world_matrix_ = moon_.toMatrix();
    earth_.setR(3);
    AddPlanet(moon_);
    AddPlanet(earth_);
}

void TwoBodySimulation::InitializeGUI()
{
    moon_.InitializeOutputs();
    moon_.InitializeControls();
}

