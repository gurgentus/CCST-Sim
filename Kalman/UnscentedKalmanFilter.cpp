#include "UnscentedKalmanFilter.hpp"
#include "CarFilterTools.hpp"
#include "Eigen/Dense"
#include <iostream>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

/**
 * Initializes Unscented Kalman filter
 */
UKF::UKF() {
  // if this is false, laser measurements will be ignored (except during init)
  use_laser_ = true;

  // if this is false, radar measurements will be ignored (except during init)
  use_radar_ = true;

  // initialize state and covariance to augmented size, will use the same
  // storage for efficiency

  // initial state vector
  x_ = VectorXd(n_aug_);

  // initial covariance matrix
  P_ = MatrixXd(n_aug_, n_aug_);

  // Process noise standard deviation longitudinal acceleration in m/s^2
  std_a_ = 0.5;

  // Process noise standard deviation yaw acceleration in rad/s^2
  std_yawdd_ = 0.5;

  // initialize the sigma matrix
  Xsig_pred_ = MatrixXd(n_aug_, 2 * n_aug_ + 1);

  // initialize the weights
  weights_ = VectorXd(2*n_aug_+1);

  // the other initializations are handled by FusionEKF since they are common to
  // KF/EKF/UKF

}

UKF::~UKF() {}

// initialize UKF with measurement matrices for LIDAR and RIDAR passed
// from FusionEKF
void UKF::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd R_in[2]) {
  R_[0] = R_in[0];
  R_[1] = R_in[1];
  x_.head(n_x_) = x_in;
  P_.topLeftCorner(n_x_, n_x_) = P_in;

  //define spreading parameter
  lambda_ = 3 - n_aug_;

  //set weights to be used later
  weights_.fill(1.0/(2*(lambda_+n_aug_)));
  weights_(0) = lambda_/(lambda_+n_aug_);
}

// PREDICT code

/**
 * Predicts sigma points, the state, and the state covariance matrix.
 * @param {double} delta_t the change in time (in seconds) between the last
 * measurement and this one.
 */
void UKF::Prediction(double delta_t) {
  //set the weights
  weights_.fill(1.0/(2*(lambda_+n_aug_)));
  weights_(0) = lambda_/(lambda_+n_aug_);

  GenerateAugmentedSigmaPoints();
  SigmaPointPrediction(delta_t);
  PredictMeanAndCovariance();
}

// generates augmented sigma points, populating the augmented entries of
// the state and covariance for efficiency
void UKF::GenerateAugmentedSigmaPoints()
{
  // augment the state with zero means
  x_(n_x_) = 0;
  x_(n_x_+1) = 0;

  // augment the covariance matrix with corresponding variances
  P_.bottomRows(2).fill(0);
  P_.rightCols(2).fill(0);
  P_(n_x_, n_x_) = std_a_*std_a_;
  P_(n_x_+1, n_x_+1) = std_yawdd_*std_yawdd_;

  //create square root matrix
  MatrixXd A = MatrixXd(n_aug_, n_aug_);
  A = P_.llt().matrixL();

  //create augmented sigma points
  Xsig_pred_.col(0) = x_;
  for (int i=0; i<n_aug_; i++)
  {
    Xsig_pred_.col(1+i) = x_ + sqrt(lambda_+n_aug_)*(A.col(i));
    Xsig_pred_.col(1+n_aug_+i) = x_ - sqrt(lambda_+n_aug_)*(A.col(i));
  }

}

// makes sigma point predictions
void UKF::SigmaPointPrediction(double delta_t)
{

  //predict sigma points
  double half_delta_t_sq = 0.5*delta_t*delta_t;
  double v, psi, psidot, nua, nupsi;
  for (int i=0; i< 2 * n_aug_ + 1; i++)
  {
      v = Xsig_pred_(2,i);
      psi = Xsig_pred_(3,i);
      psidot = Xsig_pred_(4,i);
      nua = Xsig_pred_(5,i);
      nupsi = Xsig_pred_(6,i);

      //angle normalization
      while (psi > M_PI) psi-=2.*M_PI;
      while (psi<-M_PI) psi+=2.*M_PI;

      if (fabs(psidot) < 0.0001)
      {
          Xsig_pred_(0,i) += v*cos(psi)*delta_t + half_delta_t_sq*cos(psi)*nua;
          Xsig_pred_(1,i) += v*sin(psi)*delta_t + half_delta_t_sq*sin(psi)*nua;
          Xsig_pred_(2,i) += delta_t*nua;
          Xsig_pred_(3,i) = psi + psidot*delta_t + half_delta_t_sq*nupsi;
          Xsig_pred_(4,i) += delta_t*nupsi;
      }
      else
      {
          Xsig_pred_(0,i) += (v/psidot)*(sin(psi + psidot*delta_t) -
          sin(psi))+half_delta_t_sq*cos(psi)*nua;
          Xsig_pred_(1,i) += (v/psidot)*(-cos(psi + psidot*delta_t) +
          cos(psi))+half_delta_t_sq*sin(psi)*nua;
          Xsig_pred_(2,i) += delta_t*nua;
          Xsig_pred_(3,i) = psi + psidot*delta_t + half_delta_t_sq*nupsi;
          Xsig_pred_(4,i) += delta_t*nupsi;
      }

  }

}

// use block operations instead of creating new storage for augmented matrix
void UKF::PredictMeanAndCovariance()
{
  //predict state mean
  x_.fill(0.0);
  for (int i=0; i< 2*n_aug_+1; i++)
  {
      x_.head(n_x_) = x_.head(n_x_) + weights_(i)*Xsig_pred_.topRows(n_x_).col(i);
  }

  //predict state covariance matrix
  P_.fill(0.0);
  for (int i=0; i< 2*n_aug_+1; i++)
  {
      // state difference
      VectorXd x_diff = Xsig_pred_.topRows(n_x_).col(i) - x_.head(n_x_);

      //angle normalization
      while (x_diff(3)> M_PI) x_diff(3)-=2.*M_PI;
      while (x_diff(3)<-M_PI) x_diff(3)+=2.*M_PI;

      P_.topLeftCorner(n_x_,n_x_) = P_.topLeftCorner(n_x_,n_x_) +
        weights_(i)*(x_diff)*x_diff.transpose();
  }
}


// UPDATE code


/**
 * Updates the state and the state covariance matrix using a laser measurement.
 * @param {MeasurementPackage} meas_package
 */
void UKF::UpdateLidar(const VectorXd &z) {

  // set measurement dimension, radar can measure r, phi, and r_dot
  n_z_ = 2;

  // create matrix for sigma points in measurement space
  Zsig_ = MatrixXd(n_z_, 2 * n_aug_ + 1);

  // transform sigma points into measurement space
  for (int i=0; i<2*n_aug_+1; i++)
  {
    Zsig_(0,i) = Xsig_pred_(0,i);
    Zsig_(1,i) = Xsig_pred_(1,i);
  }

  // update using common code for LIDAR and RADAR
  NIS_laser_ = Update(z, R_[0], false);
}

/**
 * Updates the state and the state covariance matrix using a radar measurement.
 * @param {MeasurementPackage} meas_package
 */
void UKF::UpdateRadar(const VectorXd &z) {

  //set measurement dimension, radar can measure r, phi, and r_dot
  n_z_ = 3;

  //create matrix for sigma points in measurement space
  Zsig_ = MatrixXd(n_z_, 2 * n_aug_ + 1);

  //transform sigma points into measurement space
  for (int i=0; i<2*n_aug_+1; i++)
  {
    Zsig_(0,i) = sqrt(Xsig_pred_(0,i)*Xsig_pred_(0,i)+Xsig_pred_(1,i)*Xsig_pred_(1,i));
    Zsig_(1,i) = atan2(Xsig_pred_(1,i), Xsig_pred_(0,i));
    Zsig_(2,i) = (Xsig_pred_(0,i)*cos(Xsig_pred_(3,i))*Xsig_pred_(2,i)+
        Xsig_pred_(1,i)*sin(Xsig_pred_(3,i))*Xsig_pred_(2,i))/Zsig_(0,i);

  }

  // for (int i = 0; i < 2 * n_aug_ + 1; i++) {  //2n+1 simga points
  //
  // // extract values for better readibility
  // double p_x = Xsig_pred_(0,i);
  // double p_y = Xsig_pred_(1,i);
  // double v  = Xsig_pred_(2,i);
  // double yaw = Xsig_pred_(3,i);
  //
  // double v1 = cos(yaw)*v;
  // double v2 = sin(yaw)*v;
  //
  // // measurement model
  // Zsig_(0,i) = sqrt(p_x*p_x + p_y*p_y);                        //r
  // Zsig_(1,i) = atan2(p_y,p_x);                                 //phi
  // Zsig_(2,i) = (p_x*v1 + p_y*v2 ) / sqrt(p_x*p_x + p_y*p_y);   //r_dot
  // }


  // update using common code for LIDAR and RADAR
  NIS_radar_ = Update(z, R_[1], true);

}


// Common Update code for LIDAR and RADAR
// Pass in the measurement and measurement noise
// which is different for LIDAR and RADAR
double UKF::Update(const VectorXd &z, const MatrixXd& R, bool normalize)
{
  weights_.fill(1.0/(2*(lambda_+n_aug_)));
  weights_(0) = lambda_/(lambda_+n_aug_);

  //mean predicted measurement
  VectorXd z_pred = VectorXd(n_z_);

  //measurement covariance matrix S
  MatrixXd S = MatrixXd(n_z_,n_z_);

  //calculate mean predicted measurement
  z_pred.fill(0);
  for (int i=0; i<2*n_aug_+1; i++)
  {
      z_pred = z_pred + weights_(i)*Zsig_.col(i);
  }

  //calculate measurement covariance matrix S
  S.fill(0);
  for (int i=0; i<2*n_aug_+1; i++)
  {
    //residual
    VectorXd z_diff = Zsig_.col(i) - z_pred;
    //angle normalization
    if (normalize == true)
    {
      while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
      while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;
    }
    S = S + weights_(i)*z_diff*z_diff.transpose();
  }
  S = S + R;

  // update step

  //create matrix for cross correlation Tc
  MatrixXd Tc = MatrixXd(n_x_, n_z_);

  //calculate cross correlation matrix
  Tc.fill(0);
  for (int i=0; i<2*n_aug_+1; i++)
  {
    VectorXd z_diff = Zsig_.col(i) - z_pred;
    //angle normalization
    if (normalize == true)
    {
      while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
      while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;
    }
    // state difference
    VectorXd x_diff = Xsig_pred_.topRows(n_x_).col(i) - x_.head(n_x_);
    //angle normalization
    while (x_diff(3)> M_PI) x_diff(3)-=2.*M_PI;
    while (x_diff(3)<-M_PI) x_diff(3)+=2.*M_PI;

    Tc = Tc + weights_(i)*x_diff*z_diff.transpose();
  }
  //calculate Kalman gain K;
  MatrixXd K = MatrixXd(n_x_, n_z_);

  K = Tc*S.inverse();

  //residual
  VectorXd z_diff = z - z_pred;

  //angle normalization
  if (normalize == true)
  {
    while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
    while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;
  }

  //update state mean and covariance matrix
  x_.head(n_x_) = x_.head(n_x_) + K*z_diff;
  while (x_(3)> M_PI) x_(3)-=2.*M_PI;
  while (x_(3)<-M_PI) x_(3)+=2.*M_PI;


  P_.topLeftCorner(n_x_,n_x_) = P_.topLeftCorner(n_x_,n_x_) - K*S*K.transpose();

  double NIS = z_diff.transpose()*S.inverse()*z_diff;

  return NIS;
}
