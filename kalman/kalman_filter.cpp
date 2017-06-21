#include "kalman_filter.h"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

const double omega_E = 2*M_PI/86164;

KalmanFilter::KalmanFilter() {
  R_[0] = MatrixXd(6, 6);
  R_[1] = MatrixXd(1, 1);
  R_[2] = MatrixXd(1, 1);
  H_[0] = MatrixXd(6, 18);
  H_[1] = MatrixXd(1, 18);
  H_[2] = MatrixXd(1, 18);
}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd x_in, MatrixXd P_in, MatrixXd &F_in,
                        MatrixXd H_in[2], MatrixXd R_in[2], MatrixXd Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = Eigen::MatrixXd(18,18);
  H_[0] = H_in[0];
  H_[1] = H_in[1];
  H_[2] = H_in[2];
  R_[0] = R_in[0];
  R_[1] = R_in[1];
  R_[2] = R_in[2];
  Q_ = Q_in;
  simulator.InitialConditions();
  simulator.getState(x_);
}

void KalmanFilter::Predict(double dt) {
  /**
    * predict the state
  */

  //F_ = I + A*dt + A*A*dt*dt/2 + A*A*A*dt*dt*dt/6 + A*A*A*A*dt*dt*dt*dt/24 + A*A*A*A*A*dt*dt*dt*dt*dt/120;

  // set the process covariance matrix Q, will need to tune
  Eigen::MatrixXd I = MatrixXd::Identity(x_.size(), x_.size());
  Q_ = 0.0001*dt*I;
  Q_(6,6) = 0.00000001;
  Q_(7,7) = 0.00000001;
  Q_(8,8) = 0.00000001;

  std::cout << "FILTER INTEGRATING FORWARD: " << dt << "s";

  simulator.setState(x_);
  simulator.UpdateState(dt);
  simulator.getState(x_);

  simulator.getTransitionMatrix(F_);
  std::cout << "F: " << F_ << std::endl;
  std::cout << "P: " << P_ << std::endl;
  P_ = F_ * P_ * F_.transpose() + Q_;
}

void KalmanFilter::Update(const Eigen::VectorXd &y, const Eigen::MatrixXd& H, const Eigen::MatrixXd& R) {
  long x_size = x_.size();
  long y_size = y.size();
  Eigen::MatrixXd I = MatrixXd::Identity(x_size, x_size);
  Eigen::MatrixXd Ht = H.transpose();
  Eigen::MatrixXd S = H * P_ * Ht + R;
  // use Cholesky decomposition instead of inverse
  Eigen::MatrixXd D = S.llt().solve(MatrixXd::Identity(y_size, y_size));
  //Eigen::MatrixXd K = P_ * Ht * S.inverse();
  Eigen::MatrixXd K = P_ * Ht * D;

  //new estimate
  x_ = x_ + (K * y);

  Eigen::MatrixXd P_temp = (I - K * H) * P_;
  P_ = P_temp;
  std::cout << "Op norm: " << P_.operatorNorm() << std::endl;
}

void KalmanFilter::UpdateKF(const VectorXd &z) {
  /**
    * update the state by using Kalman Filter equations
    * with linear measurement model
  */
  VectorXd y = z - H_[0] * x_;
  Update(y, H_[0], R_[0]);
}

void KalmanFilter::UpdateEKF(const Eigen::VectorXd& z)
{
    VectorXd h = VectorXd(6);
    for (unsigned int sensor=0; sensor<3; sensor++) {
        h(2*sensor) = sqrt((x_(0)-x_(9+3*sensor))*(x_(0)-x_(9+3*sensor))+(x_(1)-x_(10+3*sensor))*(x_(1)-x_(10+3*sensor))
                      + (x_(2)-x_(11+3*sensor))*(x_(2)-x_(11+3*sensor)));
        h(2*sensor+1) = ((x_(0)-x_(9+3*sensor))*(x_(3)+x_(10+3*sensor)*omega_E)
                +(x_(1)-x_(10+3*sensor))*(x_(4)-x_(9+3*sensor)*omega_E) + (x_(2)-x_(11+3*sensor))*x_(5))/h(2*sensor);
    }

    VectorXd y = z - h;
    std::cout << "z: " << z << std::endl;
    std::cout << "h: " << h << std::endl;
    std::cout << "diff: " << y << std::endl;
    std::cout << "estimated station cords: " << x_(9) << " " << x_(10) << " " << x_(11);
    //compute the Jacobian matrix
    H_[0] = Eigen::MatrixXd::Zero(6,18);
    for (unsigned int sensor=0; sensor<3; sensor++) {
        H_[0](2*sensor,0) = (x_(0)-x_(9+3*sensor))/h(sensor);
        H_[0](2*sensor,1) = (x_(1)-x_(10+3*sensor))/h(sensor);
        H_[0](2*sensor,2) = (x_(2)-x_(11+3*sensor))/h(sensor);

        H_[0](2*sensor, 9+3*sensor) = -(x_(0)-x_(9+3*sensor))/h(sensor);
        H_[0](2*sensor, 10+3*sensor) = -(x_(1)-x_(10+3*sensor))/h(sensor);
        H_[0](2*sensor, 11+3*sensor) = -(x_(2)-x_(11+3*sensor))/h(sensor);
    }
    for (unsigned int sensor=0; sensor<3; sensor++) {
        double B = h(2*sensor+1)/h(2*sensor);

        H_[0](2*sensor+1,0) = -B*H_[0](2*sensor,0)+(x_(3)+omega_E*x_(10+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1,1) = -B*H_[0](2*sensor,1)+(x_(4)-omega_E*x_(9+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1,2) = -B*H_[0](2*sensor,2)+(x_(5))/h(2*sensor);

        H_[0](2*sensor+1,3) = (x_(0)-x_(9+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1,4) = (x_(1)-x_(10+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1,5) = (x_(2)-x_(11+3*sensor))/h(2*sensor);

        H_[0](2*sensor+1, 9+3*sensor) = -B*H_[0](2*sensor,9+3*sensor)-(x_(3)+omega_E*x_(10+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1, 10+3*sensor) = -B*H_[0](2*sensor,10+3*sensor)-(x_(4)-omega_E*x_(9+3*sensor))/h(2*sensor);
        H_[0](2*sensor+1, 11+3*sensor) = -B*H_[0](2*sensor,11+3*sensor)-(x_(5))/h(2*sensor);
    }
    Update(y, H_[0], R_[0]);
}
void KalmanFilter::UpdateEKF(const VectorXd &z, int sensor) {
  /**
    * update the state by using Extended Kalman Filter equations
  */

  VectorXd h = VectorXd(1);
    std::cout << "gs est: " << x_(9) << " " << x_(10) << " " << x_(11) << std::endl;
  double range = sqrt((x_(0)-x_(9+3*sensor))*(x_(0)-x_(9+3*sensor))+(x_(1)-x_(10+3*sensor))*(x_(1)-x_(10+3*sensor))
                    + (x_(2)-x_(11+3*sensor))*(x_(2)-x_(11+3*sensor)));
//  double rhodot = ( (x_(0)-x_(9+3*sensor))*(x_(3)+x_(10+3*sensor)*omega_E)
//                  + (x_(1)-x_(10+3*sensor))*(x_(4)-x_(9+3*sensor)*omega_E) +  (x_(2)-x_(11+3*sensor))*(x_(5)) )/rho;
  // state to measurement function
  h << range;

  VectorXd y = z - h;
  std::cout << "err: " << z << " " << h << "diff: " << y << std::endl;

  //compute the Jacobian matrix
  H_[sensor] << (x_(0)-x_(9+3*sensor))/range, (x_(1)-x_(10+3*sensor))/range, (x_(2)-x_(11+3*sensor))/range,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0;
  H_[sensor](0, 9+3*sensor) = -(x_(0)-x_(9+3*sensor))/range;
  H_[sensor](0, 10+3*sensor) = -(x_(1)-x_(10+3*sensor))/range;
  H_[sensor](0, 11+3*sensor) = -(x_(2)-x_(11+3*sensor))/range;

  Update(y, H_[sensor], R_[sensor]);

}
