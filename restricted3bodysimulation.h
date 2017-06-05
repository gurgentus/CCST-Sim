#ifndef RESTRICTED3BODYSIMULATION_H
#define RESTRICTED3BODYSIMULATION_H

#include <objects/planet.h>
#include <orbitalsimulation.h>
#include <nums/Restricted3BodySolver.h>

class Restricted3BodySimulation : public OrbitalSimulation
{
public:
    Planet earth_;
    Planet moon_;
    Planet sat_;

    // For orbital mechanics simulation logic
    Restricted3BodySolver simulator;

    void InitializeSimulation();
    void InitializeGUI();

    void PlotSimulation();
};

#endif // RESTRICTED3BODYSIMULATION_H
