#include <iostream>
#include "CarFilterTools.hpp"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
    * Calculate the RMSE here.
  */

	VectorXd rmse(4);
	rmse << 0,0,0,0;

  if (estimations.size() == 0 || estimations.size() != ground_truth.size())
  {
      std::cout << "Error" << std::endl;
      return rmse;
  }
	//accumulate squared residuals
	for(unsigned int i=0; i < estimations.size(); ++i){
	    VectorXd temp = estimations[i]-ground_truth[i];
      VectorXd temp2 = temp.array()*temp.array();
      rmse = rmse + temp2;
	}

	//calculate the mean
	rmse = rmse/estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;

}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
    * Calculate a Jacobian here.
  */
  MatrixXd Hj(3,4);
  //recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);

  //check division by zero
  if (fabs(px) < 0.0001)
  {
    px = 0.0001;
  }
  if (fabs(py) < 0.0001)
  {
    py = 0.0001;
  }

  float rhosq = px*px + py*py;
  float rho = sqrt(rhosq);

  //compute the Jacobian matrix
  Hj << px/rho, py/rho, 0, 0,
      -py/rhosq, px/rhosq, 0, 0,
      py*(vx*py-vy*px)/pow(rhosq,3), px*(vy*px-vx*py)/pow(rhosq,3), px/rho, py/rho;

  return Hj;
}
