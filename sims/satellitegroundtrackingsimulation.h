#ifndef SATELLITEGROUNDTRACKINGSIMULATION_H
#define SATELLITEGROUNDTRACKINGSIMULATION_H

#include "orbitalsimulation.h"
#include <objects/planet.h>
#include <nums/Restricted3BodySolver.h>

class SatelliteGroundTrackingSimulation : public OrbitalSimulation
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

#endif // SATELLITEGROUNDTRACKINGSIMULATION_H
