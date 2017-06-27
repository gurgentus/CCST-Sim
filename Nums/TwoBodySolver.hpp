#ifndef TWOBODYSOLVER_H
#define TWOBODYSOLVER_H

#include "RungeKuttaSolver.hpp"

#include "Common/Output.hpp"
#include "Orbital/Omt.hpp"
#include "Eigen/Dense"

#include <QVector3D>

using namespace std;

class TwoBodySolver : public RungeKuttaSolver
{
public:
    // orbital mechanics toolbox
    Omt omt;
    // define initial conditions and the dynamics equation
    void InitialConditions();
    void InitialConditions(Eigen::Vector3d r, Eigen::Vector3d v);
    void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f);
    // outputs from the simulation
    QVector3D position();
    QVector3D velocity();
    double eccentricity();
};

#endif // TWOBODYSOLVER_H
