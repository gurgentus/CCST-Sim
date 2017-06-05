#ifndef TWOBODYSOLVER_H
#define TWOBODYSOLVER_H

#include <QVector3D>
#include "RungeKuttaSolver.hpp"

using namespace std;

class TwoBodySolver : public RungeKuttaSolver
{
public:
    // define initial conditions and the dynamics equation
    void InitialConditions();
    void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f);
    // outputs from the simulation
    QVector3D position();
    QVector3D velocity();
    double eccentricity();

};

#endif // TWOBODYSOLVER_H
