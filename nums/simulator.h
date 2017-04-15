#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QVector3D>
#include "RungeKuttaSolver.hpp"

using namespace std;

class Simulator
{
public:
    void simulate();
    void update_state(double dt);

    RungeKuttaSolver rk;
    vector<QVector3D> results;
    double t_;
    std::vector<double> state;
    QVector3D position();
};

#endif // SIMULATOR_H
