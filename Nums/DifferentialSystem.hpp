#ifndef DIFFERENTIALSYSTEM
#define DIFFERENTIALSYSTEM

#include "Eigen/Dense"

class DifferentialSystem
{
   friend class BoundaryValueProblem;
private:
   // Eigen::MatrixXd coeffs_;     // Coefficient matrix of the ODE system
   Eigen::VectorXd (*p_RhsFunc)(double t, const Eigen::VectorXd& y);  // Function on RHS of ODE
   Eigen::MatrixXd (*p_RhsGradYFunc)(double t, const Eigen::VectorXd& y);  // Gradient with respect to y

   Eigen::VectorXd (*p_BcsFunc)(const Eigen::VectorXd& left_bc, const Eigen::VectorXd& right_bc);  // Boundary condition function
   Eigen::MatrixXd (*p_BcsGrad1Func)(const Eigen::VectorXd& left_bc, const Eigen::VectorXd& right_bc);  // Gradient wrt first var
   Eigen::MatrixXd (*p_BcsGrad2Func)(const Eigen::VectorXd& left_bc, const Eigen::VectorXd& right_bc);  // Gradient wrt to second var


   // Interval for domain
   double t_min_;
   double t_max_;
public:
   DifferentialSystem(Eigen::VectorXd (*rhs)(double, const Eigen::VectorXd&),
                      Eigen::MatrixXd (*rhs_grad)(double, const Eigen::VectorXd&),
                      Eigen::VectorXd (*bc)(const Eigen::VectorXd& y1, const Eigen::VectorXd& y),
                      Eigen::MatrixXd (*bc_grad1)(const Eigen::VectorXd& y1, const Eigen::VectorXd& y),
                      Eigen::MatrixXd (*bc_grad2)(const Eigen::VectorXd& y1, const Eigen::VectorXd& y),
                      double t_min, double t_max);

};

#endif
