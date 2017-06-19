#include "OrbitDeterminationFilter.h"
#include <iostream>

OrbitDeterminationFilter::OrbitDeterminationFilter()
{
    is_initialized_ = false;
    previous_timestamp_ = 0;

    // NUMSENSORS is 3 for this case corresponding to three tracking stations
    // affecting the measurement matrix H
    MatrixXd H_array[NUMSENSORS_];
    MatrixXd R_array[NUMSENSORS_];

    // initializing matrices
    H_array[0] = MatrixXd(1, 18);
    H_array[1] = MatrixXd(1, 18);
    H_array[2] = MatrixXd(1, 18);

    R_array[0] = MatrixXd(1, 1);
    R_array[1] = MatrixXd(1, 1);
    R_array[2] = MatrixXd(1, 1);

    // Radar measurement noise standard deviation range in km
    double var_radr_ = 100;

    // measurement covariance matrices
    R_array[0] << var_radr_;
    R_array[1] << var_radr_;
    R_array[2] << var_radr_;

    // measurement matrices, not used for UKF, comment for Unscented Kalman Filter
    H_array[0] << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

    H_array[1] << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

    H_array[2] << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

    // initialize state [x, y, z, u, v, w, mu, J2, C_D, x_s1, y_s1, z_s1, x_s2, y_s2, z_s2, x_s3, y_s3, z_s3]
    // last 9 elements are the three station locations
    VectorXd x = VectorXd(18);
    const double G = 6.67259e-20;
    const double m1 = 5.974e24;
    double initmu = G*m1; //3.986004415e5;
    x << 757.7, 5222.607, 4851.5, 2.21321, 4.67834, -5.37130, initmu, 1.082626925638815e-3, 2, -5127.51, -3794.16, 0.0, 3860.91, 3238.49, 3898.094, 549.505, -1380.872, 6182.197;


    // initialize P, F, and Q and the filters
    MatrixXd P = MatrixXd(18, 18);
    double uns = 1e-8;
    P <<  uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, uns;

    MatrixXd F = Eigen::MatrixXd::Zero(18, 18);
    MatrixXd Q = MatrixXd(18, 18);

    // initialize the extended Kalman filter
    ekf_.Init(x, P, F,
         H_array, R_array, Q);

    // initialize the unscented Kalman Filter
    //ukf_.Init(x, P, R_array);

}


// processes each measurement depending if it's station
void OrbitDeterminationFilter::ProcessMeasurement(const MeasurementPackage &measurement_pack, double time) {


  /*****************************************************************************
   *  Initialization
   ****************************************************************************/
  if (!is_initialized_) {
    // can switch some of the stations off for debugging
    if ((measurement_pack.sensor_type_ == MeasurementPackage::STATION1) ||
    (measurement_pack.sensor_type_ == MeasurementPackage::STATION2) ||
    (measurement_pack.sensor_type_ == MeasurementPackage::STATION3))  {

      // can choose between KF/EKF:
      // note: none of the state variables are not observed
      // so will not update the initial state based on the observations
      // ekf_.x_ <<

      // or UKF:
      // state vector is different for our ukf model
      // [px, py, v, phi, phidot], note: phidot not observed
      // the last two are placeholders and will get overwritten by augmentation
      //if (fabs(rho) < 0.01)
      //{
      //  return;
      //}
      //ukf_.x_ << rho*cos(phi), rho*sin(phi), rho_prime, phi, 0, 0, 0;
    }

    // initialize timestamp
    previous_timestamp_ = time;

    // done initializing, no need to predict or update
    is_initialized_ = true;
    return;
  }

  /*****************************************************************************
   *  Prediction
   ****************************************************************************/

  // Update the state transition matrix F according to the new elapsed time in seconds

  //compute the time elapsed between the current and previous measurements
  float dt = (time - previous_timestamp_); // / 1000000.0;	//dt - expressed in seconds
  previous_timestamp_ = time;

  std::cout << "Fusion: " << previous_timestamp_ << std::endl;
  std::cout << "Time Filter: " << dt << std::endl;

  // predict
  // choose between KF/EKF:
//  double tm = 0;
//  double h = 0.1;
//  while (tm < dt) {
    ekf_.Predict(dt);
//    tm = tm + h;
//  }

  // or UKF:
  //ukf_.Prediction(dt);

  /*****************************************************************************
   *  Update
   ****************************************************************************/

  if (time > measurement_pack.timestamp_)
  {
      std::cout << "received measurement" << std::endl;
      if (measurement_pack.sensor_type_ == MeasurementPackage::STATION1) {
        // Radar updates
        // ekf_.UpdateEKF(measurement_pack.raw_measurements_);
        ekf_.UpdateEKF(measurement_pack.raw_measurements_, 0);
      }
      if (measurement_pack.sensor_type_ == MeasurementPackage::STATION2) {
        // Radar updates
        // ekf_.UpdateEKF(measurement_pack.raw_measurements_);
        ekf_.UpdateEKF(measurement_pack.raw_measurements_, 1);
      }
      if (measurement_pack.sensor_type_ == MeasurementPackage::STATION3) {
        // Radar updates
        // ekf_.UpdateEKF(measurement_pack.raw_measurements_);
        ekf_.UpdateEKF(measurement_pack.raw_measurements_, 2);
      }
  }
}

