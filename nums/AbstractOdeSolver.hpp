#ifndef ABSTRACTODESOLVERDEF
#define ABSTRACTODESOLVERDEF

#include <vector>

class AbstractOdeSolver
{
protected:
    double mStepSize;
    double mInitialTime;
    double mFinalTime;
    double mInitialValue;
    std::vector<double> mInitialValueVector;
public:
    void SetStepSize(double h);
    void SetTimeInterval(double t0, double t1);
    void SetInitialValue(double y0);
    void SetInitialValue(std::vector<double> y0);
    virtual double RightHandSide(double y, double t) = 0;
    virtual void SolveEquation(std::vector<double> yi) = 0;
    virtual double SolveScalarEquation() = 0;
};

#endif
