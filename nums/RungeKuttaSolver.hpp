#ifndef RUNGEKUTTASOLVER
#define RUNGEKUTTASOLVER

#include "AbstractOdeSolver.hpp"

class RungeKuttaSolver: public AbstractOdeSolver
{
public:
    double RightHandSide(double y, double t);
    double SolveScalarEquation();
    void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f);
    void SolveEquation(std::vector<double> yi);
    void RKIteration(double ti, std::vector<double> &yi);
};

#endif
