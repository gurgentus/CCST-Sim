#include "AdaptiveRungeKuttaSolver.hpp"

#include "AbstractOdeSolver.hpp"
#include <iostream>
#include <cmath>


void AdaptiveRungeKuttaSolver::SetStateDimension(int state_dim)
{
    state_dim_ = state_dim;
    state.reserve(state_dim);
}

void AdaptiveRungeKuttaSolver::UpdateState(double dt)
{
    double total_d = 0;
    while (total_d <= dt)
    {
        RKIteration(t_, state);
        total_d += mStepSize;
    }
    t_ = t_ + total_d;
}

void AdaptiveRungeKuttaSolver::RKIteration(double ti, std::vector<double>& yi)
{
    std::vector<double> k1(state_dim_);
    std::vector<double> k2(state_dim_);
    std::vector<double> k3(state_dim_);
    std::vector<double> k4(state_dim_);
    std::vector<double> k5(state_dim_);
    std::vector<double> f1(state_dim_);
    std::vector<double> f2(state_dim_);
    std::vector<double> f3(state_dim_);
    std::vector<double> f4(state_dim_);
    std::vector<double> f5(state_dim_);
    std::vector<double> f6(state_dim_);
    std::vector<double> int2(state_dim_);
    std::vector<double> int3(state_dim_);
    std::vector<double> int4(state_dim_);
    std::vector<double> int5(state_dim_);
    std::vector<double> int6(state_dim_);
    std::vector<double> e(state_dim_);
    double tol = 0.5;

    for (int it=0; it < 10; it++)
    {
        RightHandSide(ti, yi, f1);
        for (int j=0; j < state_dim_; j++)
        {
            k1[j] = mStepSize*f1[j];
            int2[j] = yi[j] + 0.25 * k1[j];
        }
        RightHandSide(ti+0.25*mStepSize, int2, f2);
        for (int j=0; j < state_dim_; j++)
        {
            k2[j] = mStepSize*f2[j];
            int3[j] = yi[j] + (3/32)*k1[j] + (9/32) * k2[j];
        }
        RightHandSide(ti+(3.0/8.0)*mStepSize, int3, f3);
        for (int j=0; j < state_dim_; j++)
        {
            k3[j] = mStepSize*f3[j];
            int4[j] = yi[j]+(1932.0/2197.0)*k1[j] + (-7200.0/2197.0)*k2[j] + (7296.0/2197.0)*k3[j];
        }
        RightHandSide(ti+(12.0/13.0)*mStepSize, int4, f4);
        for (int j=0; j < state_dim_; j++)
        {
            k4[j] = mStepSize*f4[j];
            int5[j] = yi[j]+(439.0/216.0)*k1[j] - 8*k2[j] + (3680.0/513.0)*k3[j] + (-845.0/4104.0)*k4[j];
        }
        RightHandSide(ti+mStepSize, int5, f5);
        for (int j=0; j < state_dim_; j++)
        {
            k5[j] = mStepSize*f5[j];
            int6[j] = yi[j]+(-8.0/27.0)*k1[j] + 2*k2[j] + (-3544.0/2565.0)*k3[j] + (1859.0/4104.0)*k4[j] + (-11.0/40.0)*k5[j];
        }
        RightHandSide(ti+0.5*mStepSize, int6, f6);
        for (int j=0; j < state_dim_; j++)
        {
            e[j] = fabs((16.0/135.0-25.0/216.0)*f1[j] + 0*f2[j] + (6656.0/12825.0-1408.0/2565.0)*f3[j]
                    + (28561.0/56430.0-2197.0/4104.0)*f4[j] + (-9.0/50.0+1.0/5.0)*f5[j] + (2.0/55.0)*f6[j]);
            if (e[j] <= e[0])
            {
                e[0] = e[j];
            }
        }
        double beta = 0.8;
        if (e[0] > tol)
        {
            mStepSize = mStepSize*beta*pow(tol/e[0],0.2);
        }
        else
        {
            it = 10;
        }
    }
    for (int j=0; j < state_dim_; j++)
    {
        yi[j] = yi[j] + mStepSize*((16.0/135.0)*f1[j] + (6656.0/12825.0)*f3[j] + (28561.0/56430.0)*f4[j]
            + (-9.0/50.0)*f5[j] + (2.0/55.0)*f6[j]);
    }

}


void AdaptiveRungeKuttaSolver::SolveEquation(std::vector<double> yi)
{
    double numPoints = (mFinalTime - mInitialTime)/mStepSize;
    double ti = mInitialTime;
    for (int i=0; i<state_dim_; i++ )
    {
        yi[i] = mInitialValueVector[i];
    }
    for (int i=0; i < numPoints; i++)
    {
        RKIteration(ti, yi);
        ti = ti+mStepSize;
    }

}


