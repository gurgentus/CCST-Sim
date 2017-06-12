#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
#include "Eigen/Dense"
#include "tools.h"

class KalmanFilter {
public:

  // state vector
  Eigen::VectorXd x_;

  // state covariance matrix
  Eigen::MatrixXd P_;

  // state transistion matrix
  Eigen::MatrixXd F_;

  // process covariance matrix
  Eigen::MatrixXd Q_;

  // measurement matrix
  // will contain the Jacobian for nonlinear measurement model
  Eigen::MatrixXd H_[2];

  // measurement covariance matrix
  // size 2 array for 2 measurement models
  Eigen::MatrixXd R_[2];

  /**
   * Constructor
   */
  KalmanFilter();

  /**
   * Destructor
   */
  virtual ~KalmanFilter();

  /**
   * Init Initializes Kalman filter
   * @param x_in Initial state
   * @param P_in Initial state covariance
   * @param F_in Transition matrix
   * @param H_in[] Array of Measurement matrices (or Jacobians for nonlinear)
   * @param R_in[] Measurement covariance matrices
   * @param Q_in Process covariance matrix
   */
  void Init(Eigen::VectorXd &x_in, Eigen::MatrixXd &P_in, Eigen::MatrixXd &F_in,
      Eigen::MatrixXd H_in[2], Eigen::MatrixXd R_in[2], Eigen::MatrixXd &Q_in);

  /**
   * Prediction Predicts the state and the state covariance
   * using the process model
   */
  void Predict();

  /**
   * Updates the state by using standard Kalman Filter equations
   * @param z The measurement at k+1
   */
  void UpdateKF(const Eigen::VectorXd &z);

  /**
   * Updates the state by using Extended Kalman Filter equations
   * @param z The measurement at k+1
   */
  void UpdateEKF(const Eigen::VectorXd &z);

private:
  // tool object used to compute the Jacobian
  Tools tools;
  // common operations for both KF and EKF updates
  void Update(const Eigen::VectorXd &y, const Eigen::MatrixXd& H, const Eigen::MatrixXd& R);

  // cache pi and 2pi constant values
  constexpr static const float pi_ = 3.1415926535897932384626433832795f;
  constexpr static const float _2pi_ = 2.0f * pi_;

};

#endif /* KALMAN_FILTER_H_ */
