#include "AbstractOdeSolver.hpp"
#include "ForwardEulerSolver.hpp"
#include <iostream>
#include <cmath>

double ForwardEulerSolver::RightHandSide(double t, double y)
{
    return 1+t;
}

double ForwardEulerSolver::SolveEquation()
{
    double numPoints = (mFinalTime - mInitialTime)/mStepSize;
    double ti = mInitialTime;
    double yi = mInitialValue;
    
    for (int i=0; i < numPoints; i++)
    {
        yi = yi + mStepSize*RightHandSide(ti, yi);
        ti = ti + mStepSize;
        std::cout << ti << " " << yi << std::endl;
    }
    return yi;
}
