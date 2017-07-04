#include "FusionEKF.hpp"
#include "CarFilterTools.hpp"
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

}

/**
* Destructor.
*/
FusionEKF::~FusionEKF() {}
