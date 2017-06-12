#ifndef FusionEKF_H_
#define FusionEKF_H_

#include "measurement_package.h"
#include "Eigen/Dense"
#include <vector>
#include <string>
#include <fstream>
#include "kalman_filter.h"
#include "tools.h"

#define NUMSENSORS_ 2
#define LIDAR_ 0
#define RADAR_ 1

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

private:
  // check whether the tracking toolbox was initiallized or not (first measurement)
  bool is_initialized_;

  // previous timestamp
  long previous_timestamp_;

  // tool object used to compute the RMSE
  Tools tools;

  // cache acceleration noise values for quicker computation
  constexpr static const int noise_ax = 9;
  constexpr static const int noise_ay = 9;
  constexpr static const int NaxT4 = 4*noise_ax;
  constexpr static const int NaxT2 = 2*noise_ax;
  constexpr static const int NayT4 = 4*noise_ay;
  constexpr static const int NayT2 = 2*noise_ay;

};

#endif /* FusionEKF_H_ */
