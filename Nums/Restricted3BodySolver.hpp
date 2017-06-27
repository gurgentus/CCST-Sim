#ifndef RESTRICTED3BODYSOLVER_H
#define RESTRICTED3BODYSOLVER_H

#include <QVector3D>
#include "AdaptiveRungeKuttaSolver.hpp"
#include "RungeKuttaSolver.hpp"

using namespace std;

class Restricted3BodySolver : public AdaptiveRungeKuttaSolver
{
public:
    // define initial conditions and the dynamics equation
    void InitialConditions();
    void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f);

    // outputs from the simulation
    QVector3D position();
    QVector3D velocity();
    QVector3D body1pos();
    QVector3D body2pos();
    double eccentricity();
};

#endif // RESTRICTED3BODYSOLVER_H
