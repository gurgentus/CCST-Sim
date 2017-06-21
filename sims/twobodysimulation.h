#ifndef TWOBODYSIMULATION_H
#define TWOBODYSIMULATION_H

#include "orbitalsimulation.h"
#include "objects/sbody.h"
#include "nums/earthrotationsolver.h"
#include "nums/SatelliteSolver.h"
#include "nums/TwoBodySolver.h"
#include <objects/planet.h>
#include <objects/controllable.h>
#include "kalman/OrbitDeterminationFilter.h"
#include <random>

class TwoBodySimulation : public OrbitalSimulation, public Controllable
{
public:
    OrbitDeterminationFilter filter;
    std::default_random_engine generator;

    Planet earth_;
    Planet moon_;

    // For orbital mechanics simulation logic
    SatelliteSolver sat_simulator;
    std::normal_distribution<double> distribution;
    TwoBodySolver simulator;
    EarthRotationSolver er_simulator;
    Output* e_output_; // eccentricity
    Output* h_output_; // specific angular momentum
    Output* i_output_; // inclination
    Output* Omega_output_; // right ascension of the ascending node
    Output* omega_output_; // argument of perigee
    Output* longitude_output_;
    Output* latitude_output_;
    Output* time_output_;

    bool is_initialized_ = false;
    double previous_timestamp_ = 0;
    double current_time_ = 0;
    vector<MeasurementPackage> measurement_pack_list;

    // implement inherited method from Controllable
    void UpdateControls();

    void InitializeSimulation();
    void InitializeGUI();
    void UpdateState(double dt);
    void PlotSimulation();

private:
    void check_files(ifstream& in_file, string& in_name);
};

#endif // TWOBODYSIMULATION_H
