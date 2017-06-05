#ifndef RUNGEKUTTASOLVER
#define RUNGEKUTTASOLVER

#include "AbstractOdeSolver.hpp"
#include <QVector3D>

class RungeKuttaSolver: public AbstractOdeSolver
{
private:
    int state_dim_;
protected:
    std::vector<double> state;
    std::vector<QVector3D> results;
public:
    // implementations of virtual methods from inherited class
    void UpdateState(double dt);
    void SolveEquation(std::vector<double> yi);

    // single RK iteration
    void RKIteration(double ti, std::vector<double> &yi);
    void SetStateDimension(int state_dim);

    // virtual methods
    virtual void InitialConditions() = 0;
    virtual void RightHandSide(double t, const std::vector<double> &  y, std::vector<double> &  f) = 0;
};

#endif
