#ifndef TWOBODYSIMULATION_H
#define TWOBODYSIMULATION_H

#include "orbitalsimulation.h"
#include <objects/planet.h>

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
