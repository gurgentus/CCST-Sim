#include "FusionEKF.h"
#include "tools.h"
#include "Eigen/Dense"
#include <iostream>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

/*
 * Constructor.
 */
FusionEKF::FusionEKF() {
  is_initialized_ = false;

  previous_timestamp_ = 0;

  // NUMSENSORS is 2 for this case
  // The first components store H and R for KF used with LIDAR
  // The second components store Jacobian of H and R for EKF used with RADAR
  MatrixXd H_array[NUMSENSORS_];
  MatrixXd R_array[NUMSENSORS_];

  // initializing matrices
  H_array[LIDAR_] = MatrixXd(2, 4);
  H_array[RADAR_] = MatrixXd(3, 4);
  R_array[LIDAR_] = MatrixXd(2, 2);
  R_array[RADAR_] = MatrixXd(3, 3);

  // measurement covariance matrices
  R_array[LIDAR_] << 0.0225, 0,
        0, 0.0225;
  R_array[RADAR_] << 0.09, 0, 0,
        0, 0.0009, 0,
        0, 0, 0.09;

  // measurement matrices
	H_array[LIDAR_] << 1, 0, 0, 0,
			  0, 1, 0, 0;

  H_array[RADAR_] << 1, 0, 0, 0,
			  0, 1, 0, 0,
        0, 0, 1, 0;

  // initialize state
  VectorXd x = VectorXd(4);
  x << 1, 1, 1, 1;

  // initialize P, F, and Q and the KalmanFilter
  MatrixXd P = MatrixXd(4, 4);
  P << 1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1000, 0,
        0, 0, 0, 1000;
  MatrixXd F = MatrixXd(4, 4);
  F << 1, 0, 1, 0,
        0, 1, 0, 1,
        0, 0, 1, 0,
        0, 0, 0, 1;
  MatrixXd Q = MatrixXd(4, 4);

  ekf_.Init(x, P, F,
      H_array, R_array, Q);

}

/**
* Destructor.
*/
FusionEKF::~FusionEKF() {}

void FusionEKF::ProcessMeasurement(const MeasurementPackage &measurement_pack) {


  /*****************************************************************************
   *  Initialization
   ****************************************************************************/
  if (!is_initialized_) {
    cout << "EKF: " << endl;
    if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
      /**
      Convert radar from polar to cartesian coordinates and initialize state.
      */
      float rho = measurement_pack.raw_measurements_(0);
      float phi = measurement_pack.raw_measurements_(1);
      float rho_prime = measurement_pack.raw_measurements_(2);
      ekf_.x_ << rho*cos(phi), rho*sin(phi), rho_prime*cos(phi), rho_prime*sin(phi);

    }
    else if (measurement_pack.sensor_type_ == MeasurementPackage::LASER) {
      /**
      Initialize state.
      */
      float px = measurement_pack.raw_measurements_(0);
      float py = measurement_pack.raw_measurements_(1);
      // since velocities are unknown, they are initialized to zero,
      // but with large variances
      ekf_.x_ << px, py, 0, 0;
    }

    // initialize timestamp
    previous_timestamp_ = measurement_pack.timestamp_;

    // done initializing, no need to predict or update
    is_initialized_ = true;
    return;
  }

  /*****************************************************************************
   *  Prediction
   ****************************************************************************/

  // Update the state transition matrix F according to the new elapsed time in seconds

  //compute the time elapsed between the current and previous measurements
  float dt = (measurement_pack.timestamp_ - previous_timestamp_) / 1000000.0;	//dt - expressed in seconds
  previous_timestamp_ = measurement_pack.timestamp_;

  float dt_2 = dt * dt;
  float dt_3 = dt_2 * dt;
  float dt_4 = dt_3 * dt;

  //Modify the F matrix so that the time is integrated
  ekf_.F_(0, 2) = dt;
  ekf_.F_(1, 3) = dt;

  //set the process covariance matrix Q
  ekf_.Q_ <<  dt_4/NaxT4, 0, dt_3/NaxT2, 0,
        0, dt_4/NayT4, 0, dt_3/NayT2,
        dt_3/NaxT2, 0, dt_2*noise_ax, 0,
        0, dt_3/NayT2, 0, dt_2*noise_ay;
  //predict
  ekf_.Predict();

  /*****************************************************************************
   *  Update
   ****************************************************************************/

  if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
    // Radar updates
    ekf_.UpdateEKF(measurement_pack.raw_measurements_);

  } else {
    // Laser updates
    ekf_.UpdateKF(measurement_pack.raw_measurements_);
  }

  // print the output
  cout << "x_ = " << ekf_.x_ << endl;
  cout << "P_ = " << ekf_.P_ << endl;
}
