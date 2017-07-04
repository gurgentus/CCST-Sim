#include "AbstractOdeSolver.hpp"
#include <cmath>

void AbstractOdeSolver::SetStepSize(double h)
{
    mStepSize = h;
}
void AbstractOdeSolver::SetTimeInterval(double t0, double t1)
{
    mInitialTime = t0;
    mFinalTime = t1;
}
void AbstractOdeSolver::SetInitialValue(double y0)
{
    mInitialValue = y0;
}
void AbstractOdeSolver::SetInitialValue(std::vector<double> y0)
{
    mInitialValueVector = y0;
}

double AbstractOdeSolver::time()
{
    return t_;
}
