#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cmath>
#include <QApplication>

#include "Nums/GroundTrackingSolver.hpp"

const double h = 0.01;
const double G = 6.67259e-20;
const double m1 = 5.974e24;
const double R_e = 6378.1363;
const double r_0 = 7.0e2+R_e;
const double H = 88.667;
const double sat_area = 3e-6;
const double rho_0 = 3.614e-4;
const double omega_E = 2*M_PI/86164;

void GroundTrackingSolver::InitialConditions()
{
    // state contains the state variables an
    Eigen::VectorXd Rx = Eigen::VectorXd::Zero(18+18*18);
    double initmu = G*m1; //3.986004415e5;
    Rx.head(18) << 757.7, 5222.607, 4851.5, 2.21321, 4.67834, -5.37130, initmu, 1.082626925638815e-3, 2, -5127.51, -3794.16, 0.0, 3860.91, 3238.49, 3898.094, 549.505, -1380.872, 6182.197;
    for (unsigned int i=0; i<18; i++)
    {
        Rx(18+19*i) = 1;
    }
    InitialConditions(Rx, 10);
}

void GroundTrackingSolver::InitialConditions(Eigen::VectorXd& x, double dt)
{
    RungeKuttaSolver::SetStateDimension(18+18*18);
    RungeKuttaSolver::SetStepSize(h);

    for (unsigned int i=0; i<x.size(); i++)
    {
        state[i] = x(i);
    }
    SetInitialValue(state);
    SetTimeInterval(0, dt);
    t_ = 0;
}

void GroundTrackingSolver::RightHandSide(double t, const std::vector<double> &x_, std::vector<double> &f)
{
    double x = x_[0];
    double y = x_[1];
    double z = x_[2];
    double u = x_[3];
    double v = x_[4];
    double w = x_[5];
    double uoy = u+omega_E*y;
    double vox = v-omega_E*x;
    double v_rel = sqrt(uoy*uoy+vox*vox+w*w);
    double r = sqrt(x*x+y*y+z*z);
    double rcubed = r*r*r;
    double r2five = rcubed*r*r;
    double r2six = r2five*r;
    double r2seven = r2six*r;
    double r2eight = r2seven*r;
    double r2nine = r2eight*r;

    double mu = x_[6];
    double J2 = x_[7];
    double C_D = x_[8];

    double rho = rho_0*exp(-(r-r_0)/H);
    double P_DmC = -0.5*rho*sat_area/970;

    double P_D = P_DmC*C_D;
    double P_G = mu*J2*R_e*R_e;
    double R3_15 = 1.5/r2five-7.5*z*z/r2seven;
    double R9_15 = 4.5/r2five-7.5*z*z/r2seven;
    double R15_105 = -7.5/r2seven+52.5*z*z/r2nine;
    double R45_105 = -22.5/r2seven+52.5*z*z/r2nine;
    double ReSq = R_e*R_e;

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(18, 18);

    A(0, 3) = 1;
    A(1, 4) = 1;
    A(2, 5) = 1;

    A(3, 0) = -mu/rcubed + 3*mu*x*x/r2five - P_G*(R3_15 + x*x*R15_105) + P_D*omega_E*uoy*vox/v_rel + P_D*v_rel*uoy*x/(r*H);
    A(3, 1) = 3*mu*x*y/r2five - P_G*x*y*R15_105 - P_D*omega_E*(v_rel + uoy*uoy/v_rel) + P_D*v_rel*uoy*y/(r*H);
    A(3, 2) = 3*mu*x*z/r2five - P_G*x*z*R45_105 + P_D*v_rel*uoy*z/(r*H);
    A(3, 3) = -P_D*(v_rel +  uoy*uoy/v_rel);
    A(3, 4) = -P_D*vox*uoy/v_rel;
    A(3, 5) = -P_D*uoy*w/v_rel;
    A(3, 6) = -x/rcubed - J2*ReSq*x*R3_15;
    A(3, 7) = -mu*ReSq*x*R3_15;
    A(3, 8) = P_DmC*v_rel*uoy;

    A(4, 0) = 3*mu*y*x/r2five - P_G*x*y*R15_105 - P_D*omega_E*(v_rel + vox*vox/v_rel) + P_D*v_rel*vox*x/(r*H);
    A(4, 1) = -mu/rcubed + 3*mu*y*y/r2five - P_G*(R3_15 + y*y*R15_105) - P_D*omega_E*uoy*vox/v_rel + P_D*v_rel*vox*y/(r*H);
    A(4, 2) = 3*mu*y*z/r2five - P_G*y*z*R45_105 + P_D*v_rel*vox*z/(r*H);
    A(4, 3) = -P_D*vox*uoy/v_rel;
    A(4, 4) = -P_D*(v_rel +  vox*vox/v_rel);
    A(4, 5) = -P_D*vox*w/v_rel;
    A(4, 6) = -y/rcubed - J2*ReSq*y*R3_15;
    A(4, 7) = -mu*ReSq*y*R3_15;
    A(4, 8) = P_DmC*v_rel*vox;

    A(5, 0) = 3*mu*x*z/r2five - P_G*x*z*R45_105 + P_D*omega_E*vox*w/v_rel + P_D*v_rel*w*x/(r*H);
    A(5, 1) = 3*mu*y*z/r2five - P_G*y*z*R45_105 - P_D*omega_E*uoy*w/v_rel + P_D*v_rel*w*y/(r*H);
    A(5, 2) = -mu/rcubed + 3*mu*z*z/r2five - P_G*(4.5/r2five-45*z*z/r2seven+52.5*z*z/r2nine)
             + P_D*v_rel*w*z/(r*H);
    A(5, 3) = -P_D*uoy*w/v_rel;
    A(5, 4) = -P_D*vox*w/v_rel;
    A(5, 5) = -P_D*(v_rel+w*w/v_rel);
    A(5, 6) = -z/rcubed - J2*ReSq*z*R9_15;
    A(5, 7) = -mu*ReSq*z*R9_15;
    A(5, 8) = P_DmC*v_rel*w;

    A(9, 10) = -omega_E;
    A(10, 9) = omega_E;

    A(12, 13) = -omega_E;
    A(13, 12) = omega_E;

    A(15, 16) = -omega_E;
    A(16, 15) = omega_E;

    Eigen::Vector3d pos, vel;

    pos << x_[0], x_[1], x_[2];
    vel << x_[3], x_[4], x_[5];

    f[0] = vel(0);
    f[1] = vel(1);
    f[2] = vel(2);
    f[3] = -mu*pos(0)/(r*r*r) - mu*J2*R_e*R_e*pos(0)*(1.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            + P_D*v_rel*(vel(0) + omega_E*vel(1));
    f[4] = -mu*pos(1)/(r*r*r) - mu*J2*R_e*R_e*pos(1)*(1.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            + P_D*v_rel*(vel(1) - omega_E*vel(0));
    f[5] = -mu*pos(2)/(r*r*r) - mu*J2*R_e*R_e*pos(2)*(4.5/(pow(r,5))-7.5*pos(2)*pos(2)/pow(r,7))
            + P_D*v_rel*vel(2);
    f[6] = 0;
    f[7] = 0;
    f[8] = 0;
    f[9] = x_[10]*omega_E;
    f[10] = -x_[9]*omega_E;
    f[11] = 0;
    f[12] = x_[13]*omega_E;
    f[13] = -x_[12]*omega_E;
    f[14] = 0;
    f[15] = x_[16]*omega_E;
    f[16] = -x_[15]*omega_E;
    f[17] = 0;

    for (unsigned int i=0; i<18; i++) {
        for (unsigned int j=0; j<18; j++) {
            f[18+18*i+j] =0;
            for (unsigned int k=0; k<18; k++) {
                 f[18+18*i+j] = f[18+18*i+j] + A(j,k)*x_[18+18*i+k];
            }
        }
    }

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


void GroundTrackingSolver::getState(Eigen::VectorXd& st)
{
    st = Eigen::VectorXd(18);
    for (int i=0; i<18; i++ )
    {
         st(i) = state[i];
    }
}

void GroundTrackingSolver::setState(const Eigen::VectorXd& st)
{
    for (int i=0; i<18; i++ )
    {
         state[i] = st(i);
    }
    for (unsigned int i=18; i<18+18*18; i++)
    {
        state[i] = 0;
    }
    for (unsigned int i=0; i<18; i++)
    {
        state[18+19*i] = 1;
    }
}

void GroundTrackingSolver::getTransitionMatrix(Eigen::MatrixXd& mat)
{
    for (unsigned int i=0; i<18; i++) {
        for (unsigned int j=0; j<18;j++) {
            mat(i,j) = state[18+18*j+i];
        }
    }
}
