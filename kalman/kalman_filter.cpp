#include "kalman_filter.h"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

KalmanFilter::KalmanFilter() {
  R_[0] = MatrixXd(1, 1);
  R_[1] = MatrixXd(1, 1);
  R_[2] = MatrixXd(1, 1);
  H_[0] = MatrixXd(1, 18);
  H_[1] = MatrixXd(1, 18);
  H_[2] = MatrixXd(1, 18);
}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd H_in[2], MatrixXd R_in[2], MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_[0] = H_in[0];
  H_[1] = H_in[1];
  H_[2] = H_in[2];
  R_[0] = R_in[0];
  R_[1] = R_in[1];
  R_[2] = R_in[2];
  Q_ = Q_in;
  simulator.InitialConditions();

}

const double R_e = 6378.1363;
const double rho_0 = 3.614e-22;
const double r_0 = 7.0e2+R_e;
const double H = 88.667;
const double A = 3e-6;

void KalmanFilter::Predict(double dt) {
  /**
    * predict the state
  */
  const double omega_E = 2*M_PI/86164;
  double x = x_(0);
  double y = x_(1);
  double z = x_(2);
  double u = x_(3);
  double v = x_(4);
  double w = x_(5);
  double v_rel = sqrt((u+omega_E*y)*(u+omega_E*y)+(v-omega_E*x)*(v-omega_E*x)+w*w);
  double r = sqrt(x*x+y*y+z*z);
  double rcubed = r*r*r;
  double r2five = rcubed*r*r;
  double r2six = r2five*r;
  double r2seven = r2six*r;
  double r2eight = r2seven*r;
  double r2nine = r2eight*r;

  double mu = x_(6);
  double J2 = x_(7);
  double C_D = x_(8);

  double rho = rho_0*exp(-(r-r_0)/H);
  double P_DmC = -0.5*rho*A/970;

  double P_D = P_DmC*C_D;
  double P_G = mu*J2*R_e*R_e;
  double R3_15 = 1.5/r2five-7.5*z*z/r2seven;
  double R9_15 = 4.5/r2five-7.5*z*z/r2seven;
  double R15_105 = -7.5/r2seven+52.5*z*z/r2nine;
  double R45_105 = -22.5/r2seven+52.5*z*z/r2nine;
  double ReSq = R_e*R_e;
  double uoy = u+omega_E*y;
  double vox = v-omega_E*x;

  long x_size = x_.size();
  Eigen::MatrixXd I = Eigen::MatrixXd::Identity(x_size, x_size);
  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(x_size, x_size);

  //Modify the F matrix so that the time is integrated
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

  F_ = I + A*dt + A*A*dt*dt/2 + A*A*A*dt*dt*dt/6 + A*A*A*A*dt*dt*dt*dt/24;

  // set the process covariance matrix Q, will need to tune
  Q_ = 0.01*I;

  simulator.setState(x_);
  simulator.UpdateState(dt);
  simulator.getState(x_);

  P_ = F_ * P_ * F_.transpose() + Q_;
}

void KalmanFilter::Update(const VectorXd &y, const MatrixXd& H, const MatrixXd& R) {
  MatrixXd Ht = H.transpose();
  MatrixXd S = H * P_ * Ht + R;
  MatrixXd K = P_ * Ht * S.inverse();
  //new estimate
  x_ = x_ + (K * y);
  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H) * P_;
}

void KalmanFilter::UpdateKF(const VectorXd &z) {
  /**
    * update the state by using Kalman Filter equations
    * with linear measurement model
  */
  VectorXd y = z - H_[0] * x_;
  Update(y, H_[0], R_[0]);
}

void KalmanFilter::UpdateEKF(const VectorXd &z, int sensor) {
  /**
    * update the state by using Extended Kalman Filter equations
  */

  VectorXd h = VectorXd(1);

  double range = sqrt((x_(0)-x_(9+3*sensor))*(x_(0)-x_(9+3*sensor))+(x_(1)-x_(10+3*sensor))*(x_(1)-x_(10+3*sensor))
                    + (x_(2)-x_(11+3*sensor))+(x_(2)-x_(11+3*sensor)));
//  double rhodot = ( (x_(0)-x_(9+3*sensor))*(x_(3)+x_(10+3*sensor)*omega_E)
//                  + (x_(1)-x_(10+3*sensor))*(x_(4)-x_(9+3*sensor)*omega_E) +  (x_(2)-x_(11+3*sensor))*(x_(5)) )/rho;
  // state to measurement function
  h << range;

  VectorXd y = z - h;

  //compute the Jacobian matrix
  H_[sensor] << (x_(0)-x_(9+3*sensor))/range, (x_(1)-x_(10+3*sensor))/range, (x_(2)-x_(11+3*sensor))/range,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;
  H_[sensor](0, 9+3*sensor) = -(x_(0)-x_(9+3*sensor))/range;
  H_[sensor](0, 10+3*sensor) = -(x_(1)-x_(10+3*sensor))/range;
  H_[sensor](0, 11+3*sensor) = -(x_(2)-x_(11+3*sensor))/range;

  Update(y, H_[sensor], R_[sensor]);

}
