#include "Restricted3BodySolver.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cmath>
#include <QApplication>

#include <Python.h>

#define _USE_MATH_DEFINES

const double G = 6.67259e-20;
const double m1 = 5.9742e24;
const double m2 = 7.348e22;

const double h = 1;// (tf-t0)/n;

const double mu1 = G*m1;
const double mu2 = G*m2;
const double pi1 = m1/(m1+m2);
const double pi2 = m2/(m1+m2);

const double r12 = 384400;

const double Omega = sqrt(G*(m1+m2)/(r12*r12*r12));

using namespace std;

void Restricted3BodySolver::InitialConditions()
{
    SetStateDimension(4);
    SetStepSize(h);

    double phi = -90*(M_PI/180);
    double gamma = 20*(M_PI/180);
    double vbo = 10.9148;

    state[0] = (6378+200)*cos(phi)-pi2*r12;
    state[1] = (6378+200)*sin(phi);
    state[2] = vbo*cos(phi+M_PI/2-gamma);
    state[3] = vbo*sin(phi+M_PI/2-gamma);

    SetInitialValue(state);
    SetTimeInterval(0, 400);
    t_ = 0;
}

void Restricted3BodySolver::RightHandSide(double t, const std::vector<double> &y, std::vector<double> &f)
{
    double r1 = sqrt((y[0]+pi2*r12)*(y[0]+pi2*r12)+y[1]*y[1]);
    double r2 = sqrt((y[0]-pi1*r12)*(y[0]-pi1*r12)+y[1]*y[1]);
    double r1cube = r1*r1*r1;
    double r2cube = r2*r2*r2;

    f[0] = y[2];
    f[1] = y[3];
    f[2] = 2*Omega*y[3]+Omega*Omega*y[0]-mu1*(y[0]+pi2*r12)/r1cube-mu2*(y[0]-pi1*r12)/r2cube;
    f[3] = -2*Omega*y[2]+Omega*Omega*y[1]-mu1*y[1]/r1cube-mu2*y[1]/r2cube;
}

QVector3D Restricted3BodySolver::position()
{
    return QVector3D(state[0], state[1], 0);
}
QVector3D Restricted3BodySolver::body1pos()
{
    return QVector3D(-pi2*r12, 0, 0);
}
QVector3D Restricted3BodySolver::body2pos()
{
    return QVector3D(pi1*r12, 0, 0);
}

QVector3D Restricted3BodySolver::velocity()
{
    double U;
    double V;
    double W;

    U = 0;
    V = 0;
    W = 0;

    return QVector3D(U, V, W);
}

double Restricted3BodySolver::eccentricity()
{
    return 0;
}

