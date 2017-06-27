#ifndef UKF_H
#define UKF_H

#include "MeasurementPackage.hpp"
#include "Eigen/Dense"
#include <vector>
#include <string>
#include <fstream>
#include "CarFilterTools.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class UKF {
public:

  ///* initially set to false, set to true in first call of ProcessMeasurement
  bool is_initialized_;

  ///* if this is false, laser measurements will be ignored (except for init)
  bool use_laser_;

  ///* if this is false, radar measurements will be ignored (except for init)
  bool use_radar_;

  ///* state vector: [pos1 pos2 vel_abs yaw_angle yaw_rate] in SI units and rad
  VectorXd x_;

  ///* state covariance matrix
  MatrixXd P_;

  ///* predicted sigma points matrix
  MatrixXd Xsig_pred_;

  MatrixXd Zsig_;

  ///* time when the state is true, in us
  long long time_us_;

  ///* Process noise standard deviation longitudinal acceleration in m/s^2
  double std_a_;

  ///* Process noise standard deviation yaw acceleration in rad/s^2
  double std_yawdd_;

  // ///* Laser measurement noise standard deviation position1 in m
  // double std_laspx_;
  //
  // ///* Laser measurement noise standard deviation position2 in m
  // double std_laspy_;
  //
  // ///* Radar measurement noise standard deviation radius in m
  // double std_radr_;
  //
  // ///* Radar measurement noise standard deviation angle in rad
  // double std_radphi_;
  //
  // ///* Radar measurement noise standard deviation radius change in m/s
  // double std_radrd_ ;

  ///* Weights of sigma points
  VectorXd weights_;

  ///* State dimension
  const int n_x_ = 5;

  ///* Augmented state dimension
  const int n_aug_ = 7;

  ////* Measurement dimension - will change between radar/lidar
  int n_z_ = 3;

  ///* Sigma point spreading parameter
  double lambda_;

  ///* the current NIS for radar
  double NIS_radar_;

  ///* the current NIS for laser
  double NIS_laser_;

  // measurement covariance matrix
  // size 2 array for 2 measurement models
  Eigen::MatrixXd R_[2];

  /**
   * Constructor
   */
  UKF();

  /**
   * Destructor
   */
  virtual ~UKF();

  void Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd R_in[2]);

  /**
   * ProcessMeasurement
   * @param meas_package The latest measurement data of either radar or laser
   */
  void ProcessMeasurement(MeasurementPackage meas_package);

  /**
   * Prediction Predicts sigma points, the state, and the state covariance
   * matrix
   * @param delta_t Time between k and k+1 in s
   */
  void Prediction(double delta_t);

  // common code for ukf update, returns NIS value
  double Update(const VectorXd &z, const MatrixXd& R, bool normalize);

  /**
   * Updates the state and the state covariance matrix using a laser measurement
   * @param z The measurement at k+1
   */
  void UpdateLidar(const VectorXd &z);

  /**
   * Updates the state and the state covariance matrix using a radar measurement
   * @param z The measurement at k+1
   */
  void UpdateRadar(const VectorXd &z);

  void UpdateState(VectorXd* x_out, MatrixXd* P_out);

private:
  void GenerateAugmentedSigmaPoints();
  void SigmaPointPrediction(double delta_t);
  void PredictMeanAndCovariance();
};

#endif /* UKF_H */
