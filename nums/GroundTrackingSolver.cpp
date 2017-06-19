#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cmath>
#include <QApplication>
#include "nums/GroundTrackingSolver.h"

const double h = 0.01;
const double G = 6.67259e-20;
const double m1 = 5.974e24;
const double R_e = 6378.1363;
const double r_0 = 7.0e2+R_e;
const double H = 88.667;
const double A = 3e-6;
const double rho_0 = 3.614e-22;
const double omega_E = 2*M_PI/86164;

void GroundTrackingSolver::InitialConditions()
{
    Eigen::VectorXd Rx(18);
    double initmu = G*m1; //3.986004415e5;
    Rx << 757.7, 5222.607, 4851.5, 2.21321, 4.67834, -5.37130, initmu, 1.082626925638815e-3, 2, -5127.51, -3794.16, 0.0, 3860.91, 3238.49, 3898.094, 549.505, -1380.872, 6182.197;
    InitialConditions(Rx, 10);
}

void GroundTrackingSolver::InitialConditions(Eigen::VectorXd& x, double dt)
{
    RungeKuttaSolver::SetStateDimension(18);
    RungeKuttaSolver::SetStepSize(h);

    for (unsigned int i=0; i<x.size(); i++)
    {
        state[i] = x(i);
    }
    SetInitialValue(state);
    SetTimeInterval(0, dt);
    t_ = 0;
}

void GroundTrackingSolver::RightHandSide(double t, const std::vector<double> &y, std::vector<double> &f)
{
    Eigen::Vector3d pos, vel;
    double r = sqrt(y[0]*y[0] + y[1]*y[1] + y[2]*y[2]);
    double rho = rho_0*exp(-(r-r_0)/H);
    double mu = y[6];
    double J2 = y[7];
    double C_D = y[8];

    pos << y[0], y[1], y[2];
    vel << y[3], y[4], y[5];

    double v_rel = sqrt((vel(0)+omega_E*vel(1))*(vel(0)+omega_E*vel(1))
                        +(vel(1)-omega_E*vel(0))*(vel(1)-omega_E*vel(0))+vel(2)*vel(2));

    f[0] = vel(0);
    f[1] = vel(1);
    f[2] = vel(2);
    f[3] = -mu*pos(0)/(r*r*r) - mu*J2*R_e*R_e*pos(0)*(1.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            -0.5*rho*C_D*A*v_rel*(vel(0) + omega_E*vel(1))/970;
    f[4] = -mu*pos(1)/(r*r*r) - mu*J2*R_e*R_e*pos(1)*(1.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            -0.5*rho*C_D*A*v_rel*(vel(1) - omega_E*vel(0))/970;
    f[5] = -mu*pos(2)/(r*r*r) - mu*J2*R_e*R_e*pos(2)*(4.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            -0.5*rho*C_D*A*v_rel*vel(2)/970;
    f[6] = 0;
    f[7] = 0;
    f[8] = 0;
    f[9] = -y[10]*omega_E;
    f[10] = y[9]*omega_E;
    f[11] = 0;
    f[12] = -y[13]*omega_E;
    f[13] = y[12]*omega_E;
    f[14] = 0;
    f[15] = -y[16]*omega_E;
    f[16] = y[15]*omega_E;
    f[17] = 0;
}

QVector3D GroundTrackingSolver::position()
{
    double XG;
    double YG;
    double ZG;

    XG = state[0];
    YG = state[1];
    ZG = state[2];

    return QVector3D(XG, YG, ZG);
}
