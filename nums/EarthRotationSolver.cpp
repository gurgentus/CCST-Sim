#include "EarthRotationSolver.h"
#include <iostream>

void EarthRotationSolver::InitialConditions()
{
    t_ = 0;
}

void EarthRotationSolver::UpdateState(double dt)
{
    t_ = t_ + dt;
    rot = (-2*M_PI*dt)/(24*3600);
}
void EarthRotationSolver::SolveEquation(std::vector<double> yi) {

}
double EarthRotationSolver::rotation() {
    return rot;
}

