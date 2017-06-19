#ifndef MEASUREMENT_PACKAGE_H_
#define MEASUREMENT_PACKAGE_H_

#include "Eigen/Dense"

class OrbitMeasurementPackage {
public:
  long long timestamp_;

  enum SensorType{
    STATION1,
    STATION2,
    STATION3
  } sensor_type_;

  Eigen::VectorXd raw_measurements_;

};

#endif /* MEASUREMENT_PACKAGE_H_ */
