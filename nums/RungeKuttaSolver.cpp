#include "AbstractOdeSolver.hpp"
#include "RungeKuttaSolver.hpp"
#include <iostream>
#include <cmath>

void RungeKuttaSolver::SetStateDimension(int state_dim)
{
    state_dim_ = state_dim;
    state.reserve(state_dim);
}

void RungeKuttaSolver::SolveEquation(std::vector<double> yi)
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

void RungeKuttaSolver::UpdateState(double dt)
{
    double total_d = 0;
    while (total_d < dt)
    {
        RKIteration(t_, state);
        total_d += mStepSize;
    }
    t_ = t_ + total_d;
}

void RungeKuttaSolver::getState(Eigen::VectorXd& st)
{
    st = Eigen::VectorXd(state_dim_);
    for (int i=0; i<state_dim_; i++ )
    {
         st(i) = state[i];
    }
}

void RungeKuttaSolver::setState(const Eigen::VectorXd& st)
{
    for (int i=0; i<state_dim_; i++ )
    {
         state[i] = st(i);
    }
}

void RungeKuttaSolver::RKIteration(double ti, std::vector<double>& yi)
{
    std::vector<double> k1(state_dim_);
    std::vector<double> k2(state_dim_);
    std::vector<double> k3(state_dim_);
    std::vector<double> k4(state_dim_);
    std::vector<double> f1(state_dim_);
    std::vector<double> f2(state_dim_);
    std::vector<double> f3(state_dim_);
    std::vector<double> f4(state_dim_);
    std::vector<double> int2(state_dim_);
    std::vector<double> int3(state_dim_);
    std::vector<double> int4(state_dim_);

    RightHandSide(ti, yi, f1);
    for (int j=0; j < state_dim_; j++)
    {
        k1[j] = mStepSize*f1[j];
        int2[j] = yi[j] + 0.5 * k1[j];
    }
    RightHandSide(ti+0.5*mStepSize, int2, f2);
    for (int j=0; j < state_dim_; j++)
    {
        k2[j] = mStepSize*f2[j];
        int3[j] = yi[j] + 0.5 * k2[j];
    }
    RightHandSide(ti+0.5*mStepSize, int3, f3);
    for (int j=0; j < state_dim_; j++)
    {
        k3[j] = mStepSize*f3[j];
        int4[j] = yi[j]+k3[j];
    }

    RightHandSide(ti+mStepSize, int4, f4);
    for (int j=0; j < state_dim_; j++)
    {
        k4[j] = mStepSize*f4[j];
        yi[j] = yi[j] + (1.0/6.0)*(k1[j] + 2*k2[j] + 2*k3[j] + k4[j]);
    }

}



