#ifndef TWOBODYSIMULATION_H
#define TWOBODYSIMULATION_H

#include "orbitalsimulation.h"
#include "objects/sbody.h"
#include "nums/earthrotationsolver.h"
#include "nums/TwoBodySolver.h"
#include <objects/planet.h>
#include <objects/controllable.h>

class TwoBodySimulation : public OrbitalSimulation, public Controllable
{
public:
    Planet earth_;
    Planet moon_;

    // For orbital mechanics simulation logic
    TwoBodySolver simulator;
    EarthRotationSolver er_simulator;
    Output* e_output_; // eccentricity
    Output* h_output_; // specific angular momentum
    Output* i_output_; // inclination
    Output* Omega_output_; // right ascension of the ascending node
    Output* omega_output_; // argument of perigee
    Output* longitude_output_;
    Output* latitude_output_;

    // implement inherited method from Controllable
    void UpdateControls();

    void InitializeSimulation();
    void InitializeGUI();
    void UpdateState(double dt);
    void PlotSimulation();
};

#endif // TWOBODYSIMULATION_H
