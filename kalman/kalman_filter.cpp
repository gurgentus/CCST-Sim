#include "kalman_filter.h"
#include <iostream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

KalmanFilter::KalmanFilter() {
  R_[0] = MatrixXd(2, 2);
  R_[1] = MatrixXd(3, 3);
  H_[0] = MatrixXd(2, 4);
  H_[1] = MatrixXd(3, 4);
}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd H_in[2], MatrixXd R_in[2], MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_[0] = H_in[0];
  H_[1] = H_in[1];
  R_[0] = R_in[0];
  R_[1] = R_in[1];
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
    * predict the state
  */
  x_ = F_ * x_;
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

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
    * update the state by using Extended Kalman Filter equations
  */

  float px = x_(0);
  float py = x_(1);
  float vx = x_(2);
  float vy = x_(3);

  // if near singularity approximate with nonzero values
  if (fabs(px) < 0.0001)
  {
    px = 0.0001;
  }
  if (fabs(py) < 0.0001)
  {
    py = 0.0001;
  }

  // cache values for quicker calculation
  float rhosq = px*px + py*py;
  float rho = sqrt(rhosq);

  VectorXd h = VectorXd(3);

  // state to measurement function
  h << rho, atan2(py, px), (px*vx+py*vy)/rho;

  VectorXd y = z - h;

  // make sure the value is between -pi and pi
  if (y(1) > _2pi_)
  {
    y(1) = y(1) - _2pi_;
  }
  if (y(1) < -_2pi_)
  {
    y(1) = y(1) + _2pi_;
  }

  // update distribution based on Jacobian of the measurement function
  H_[1] = tools.CalculateJacobian(x_);
  Update(y, H_[1], R_[1]);

}
