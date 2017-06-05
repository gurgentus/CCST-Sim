#ifndef TWOBODYSIMULATION_H
#define TWOBODYSIMULATION_H

#include <objects/planet.h>
#include <orbitalsimulation.h>

class TwoBodySimulation : public OrbitalSimulation
{
public:
    Planet earth_;
    Planet moon_;

    // For orbital mechanics simulation logic
    TwoBodySolver simulator;

    void InitializeSimulation();
    void InitializeGUI();
};

#endif // TWOBODYSIMULATION_H
