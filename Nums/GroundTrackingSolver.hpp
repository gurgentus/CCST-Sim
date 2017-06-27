#ifndef GROUNDTRACKINGSOLVER_H
#define GROUNDTRACKINGSOLVER_H

#include "Common/Output.hpp"
#include "Orbital/Omt.hpp"
#include "Eigen/Dense"

#include <QVector3D>
#include <QtCharts>

#include "RungeKuttaSolver.hpp"

using namespace std;

class GroundTrackingSolver : public RungeKuttaSolver
{
public:
    // orbital mechanics toolbox
    Omt omt;
    // define initial conditions and the dynamics equation
    void InitialConditions();
    void InitialConditions(Eigen::VectorXd& x, double dt);
    void RightHandSide(double t, const std::vector<double>& x_, std::vector<double> &  f);

    void getState(Eigen::VectorXd& st);
    void setState(const Eigen::VectorXd& st);

    // outputs from the simulation
    QVector3D position();
    QVector3D velocity();
    void getTransitionMatrix(Eigen::MatrixXd& mat);

    double eccentricity();
};

#endif // GROUNDTRACKINGSOLVER_H
