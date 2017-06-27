#ifndef FusionEKF_H_
#define FusionEKF_H_

#include "MeasurementPackage.hpp"
#include "Eigen/Dense"
#include <vector>
#include <string>
#include <fstream>
#include "KalmanFilter.hpp"
#include "UnscentedKalmanFilter.hpp"
#include "CarFilterTools.hpp"

class FusionEKF {
public:
  /**
  * Constructor.
  */
  FusionEKF();

  /**
  * Destructor.
  */
  virtual ~FusionEKF();

  /**
  * Run the whole flow of the Kalman Filter from here.
  */
  void ProcessMeasurement(const MeasurementPackage &measurement_pack);

  /**
  * Kalman Filter update and prediction math lives in here.
  */
  KalmanFilter ekf_;
  UKF ukf_;
protected:
  // check whether the tracking toolbox was initiallized or not (first measurement)
  bool is_initialized_;

  // previous timestamp
  double previous_timestamp_;

  // tool object used to compute the RMSE
  Tools tools;



};

#endif /* FusionEKF_H_ */
