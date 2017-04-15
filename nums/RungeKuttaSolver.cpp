#include "AbstractOdeSolver.hpp"
#include "RungeKuttaSolver.hpp"
#include <iostream>
#include <cmath>

const double G = 6.67259e-20;
const double m1 = 1e26;
const double m2 = 1e26;

double RungeKuttaSolver::RightHandSide(double t, double y)
{
    return 1+t;
}

void RungeKuttaSolver::RightHandSide(double t, const std::vector<double> &y, std::vector<double> &f)
{
    double r = sqrt(pow(y[3]-y[0],2) + pow(y[4]-y[1],2) + pow(y[5]-y[2],2));
    f[0] = y[6];
    f[1] = y[7];
    f[2] = y[8];
    f[3] = y[9];
    f[4] = y[10];
    f[5] = y[11];
    f[6] = G*m2*(y[3]-y[0])/pow(r,3);
    f[7] = G*m2*(y[4]-y[1])/pow(r,3);
    f[8] = G*m2*(y[5]-y[2])/pow(r,3);
    f[9] = -G*m1*(y[3]-y[0])/pow(r,3);
    f[10] = -G*m1*(y[4]-y[1])/pow(r,3);
    f[11] = -G*m1*(y[5]-y[2])/pow(r,3);
}




double RungeKuttaSolver::SolveScalarEquation()
{
    double numPoints = (mFinalTime - mInitialTime)/mStepSize;
    double ti = mInitialTime;
    double yi = mInitialValue;
    
    for (int i=0; i < numPoints; i++)
    {
        double k1 = mStepSize*RightHandSide(ti, yi);
        double k2 = mStepSize*RightHandSide(ti+0.5*mStepSize, yi + 0.5*k1);
        double k3 = mStepSize*RightHandSide(ti+0.5*mStepSize, yi + 0.5*k2);
        double k4 = mStepSize*RightHandSide(ti+mStepSize, yi+k3);
        
        yi = yi + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        
        ti = ti+mStepSize;
        std::cout << ti << " " << yi << std::endl;
    }
    return yi;
}

void RungeKuttaSolver::RKIteration(double ti, std::vector<double>& yi)
{
    double k1[12];
    double k2[12];
    double k3[12];
    double k4[12];
    std::vector<double> f1(12);
    std::vector<double> f2(12);
    std::vector<double> f3(12);
    std::vector<double> f4(12);
    std::vector<double> int2(12);
    std::vector<double> int3(12);
    std::vector<double> int4(12);

    RightHandSide(ti, yi, f1);
    for (int j=0; j < 12; j++)
    {
        k1[j] = mStepSize*f1[j];
        int2[j] = yi[j] + 0.5 * k1[j];
    }
    RightHandSide(ti+0.5*mStepSize, int2, f2);
    for (int j=0; j < 12; j++)
    {
        k2[j] = mStepSize*f2[j];
        int3[j] = yi[j] + 0.5 * k2[j];
    }
    RightHandSide(ti+0.5*mStepSize, int3, f3);
    for (int j=0; j < 12; j++)
    {
        k3[j] = mStepSize*f3[j];
        int4[j] = yi[j]+k3[j];
    }

    RightHandSide(ti+mStepSize, int4, f4);
    for (int j=0; j < 12; j++)
    {
        k4[j] = mStepSize*f4[j];
        yi[j] = yi[j] + (1.0/6.0)*(k1[j] + 2*k2[j] + 2*k3[j] + k4[j]);
    }

    //std::cout << ti << " " << yi << std::endl;

}

void RungeKuttaSolver::SolveEquation(std::vector<double> yi)
{
    double numPoints = (mFinalTime - mInitialTime)/mStepSize;
    double ti = mInitialTime;
    for (int i=0; i<12; i++ )
    {
        yi[i] = mInitialValueVector[i];
    }
    for (int i=0; i < numPoints; i++)
    {
        RKIteration(ti, yi);
        ti = ti+mStepSize;
    }

}
