#ifndef GROUNDTRACKINGSOLVER_H
#define GROUNDTRACKINGSOLVER_H

#include <QVector3D>
#include <common/output.h>
#include <orbital/omt.h>
#include "Eigen/Dense"
#include <QtCharts>

#include "RungeKuttaSolver.hpp"

using namespace std;

class GroundTrackingSolver : public RungeKuttaSolver
{
public:
    // orbital mechanics toolbox
    Omt omt;
    // define initial conditions and the dynamics equation
    void InitialConditions();
    void InitialConditions(Eigen::VectorXd& x, double dt);
    void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f);
    // outputs from the simulation
    QVector3D position();
    QVector3D velocity();

    double eccentricity();
};

#endif // GROUNDTRACKINGSOLVER_H
