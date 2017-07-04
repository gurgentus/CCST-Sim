#ifndef TWOBODYSIMULATION_H
#define TWOBODYSIMULATION_H

#include "sims/orbitalsimulation.h"
#include "objects/sbody.h"
#include "nums/earthrotationsolver.h"
#include "nums/SatelliteSolver.h"
#include "nums/TwoBodySolver.h"
#include <objects/planet.h>
#include <objects/controllable.h>
#include "kalman/OrbitDeterminationFilter.h"
#include <random>

#include <QStringList>

#include <SimulationInterface.hpp>

#include <QObject>
#include <QtPlugin>



class TwoBodySimulation : public OrbitalSimulation,
                          public Controllable,
                          public SimulationInterface
{
    Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.gensim.SimulationInterface" FILE "basictools.json")
    Q_INTERFACES(SimulationInterface)

public:
    OrbitDeterminationFilter filter;
    std::default_random_engine generator;

    Planet earth_;
    Planet sat_;

    // For orbital mechanics simulation logic
    SatelliteSolver sat_simulator;
    std::normal_distribution<double> distribution;
    TwoBodySolver simulator;
    EarthRotationSolver er_simulator;
    Output* t_output_; // time
    Output* u_output_; // uncertainty
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

    QStringList Simulations() const override;
    // implement inherited method from Controllable
    void UpdateControls() override;
    void InitializeSimulation() override;
    void InitializeGUI() override;
    void UpdateState(double dt) override;
    void PlotSimulation();

private:
    void check_files(ifstream& in_file, string& in_name);
};

#endif // TWOBODYSIMULATION_H
