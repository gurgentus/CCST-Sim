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
    double t_ = 0;
    std::vector<double> mInitialValueVector;
public:
    void SetStepSize(double h);
    void SetTimeInterval(double t0, double t1);
    void SetInitialValue(double y0);
    void SetInitialValue(std::vector<double> y0);
    double time();

    // virtual methods
    virtual void InitialConditions() = 0;
    virtual void UpdateState(double dt) = 0;
    virtual void SolveEquation(std::vector<double> yi) = 0;

};

#endif
