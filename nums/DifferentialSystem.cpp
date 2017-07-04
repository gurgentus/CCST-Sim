#include <iostream>
#include <fstream>
#include <cassert>

#include "DifferentialSystem.hpp"

DifferentialSystem::DifferentialSystem(Eigen::VectorXd (*rhs)(double, const Eigen::VectorXd&),
                                       Eigen::MatrixXd (*rhs_grad)(double, const Eigen::VectorXd&),
                                       Eigen::VectorXd (*bc)(const Eigen::VectorXd &, const Eigen::VectorXd &),
                                       Eigen::MatrixXd (*bc_grad1)(const Eigen::VectorXd &, const Eigen::VectorXd &),
                                       Eigen::MatrixXd (*bc_grad2)(const Eigen::VectorXd &, const Eigen::VectorXd &),
                                       double t_min, double t_max)
{
    p_RhsFunc = rhs;
    p_RhsGradYFunc = rhs_grad;
    p_BcsFunc = bc;
    p_BcsGrad1Func = bc_grad1;
    p_BcsGrad2Func = bc_grad2;
    t_min_ = t_min;
    t_max_ = t_max;
}
