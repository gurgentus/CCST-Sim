#ifndef FORWARDEULERSOLVER
#define FORWARDEULERSOLVER

#include "AbstractOdeSolver.hpp"

class ForwardEulerSolver: public AbstractOdeSolver
{
public:
    double RightHandSide(double y, double t);
    double SolveScalarEquation();
};

#endif
