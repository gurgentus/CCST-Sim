#include <iostream>
#include <fstream>
#include <cassert>

#include "BoundaryValueProblem.hpp"

BoundaryValueProblem::BoundaryValueProblem(DifferentialSystem *p_ode, int num_nodes, int dim)
    : grid_(num_nodes, p_ode->t_min_, p_ode->t_max_)
{
    p_ode_ = p_ode;
    dim_ = dim;
    num_nodes_ = num_nodes;
    sol_vec_ = Eigen::VectorXd::Zero(num_nodes_*dim_);
//    rhs_vec_ = Eigen::VectorXd(num_nodes_*dim_);
//    coeff_matrix_ = Eigen::MatrixXd(num_nodes_*dim_, num_nodes_*dim_);
    filename_ = "ode_output.dat";
}

double BoundaryValueProblem::Step(int i)
{
    return grid_.nodes_[i].coordinate;
}
//void BoundaryValueProblem::PopulateMatrix()
//{
//    for (int i=0; i<num_nodes_; i++)
//    {
//        double xm = p_grid_->nodes_[i-1].coordinate;
//        double x = p_grid_->nodes_[i].coordinate;
//        double xp = p_grid_->nodes_[i+1].coordinate;

//        // first and last lines come from boundary conditions
//        for (int eqn=0; eqn<dim_; eqn++) // for each equation in the system
//        {
//            for (int var=0; var<dim_; var++) // and for each variable
//            {
//                // the corresponding entries in the coefficient matrix for
//                // equation number eqn and node number: i+1 are
//                // the first derivative based on the values at node i+2 and node i for variable: var
//                // and the values of all variables at node: i+1
//                (*mpLhsMat)(dim_*eqn+i+1,num_nodes*var+i) = -1/(xp-xm);
//                (*mpLhsMat)(dim_*eqn+i+1,num_nodes*var+i+1) = mpOde->mCoeffOfU(eqn, var);
//                (*mpLhsMat)(dim_*eqn+i+1,num_nodes*var+i+2) = 1/(xp-xm);
//            }
//        }
//    }
//}

void BoundaryValueProblem::Solve()
{
    for (int iter=0; iter<MAX_ITER; iter++)
    {
        Eigen::VectorXd u = Eigen::VectorXd(sol_vec_.segment(0,dim_));
        Eigen::VectorXd v = Eigen::VectorXd(sol_vec_.tail(dim_));

        Eigen::MatrixXd Ba = p_ode_->p_BcsGrad1Func(u,v);
        Eigen::MatrixXd Bb = p_ode_->p_BcsGrad2Func(u,v);
        Eigen::VectorXd beta = -p_ode_->p_BcsFunc(u,v);

        Eigen::MatrixXd LeftMatrix = Eigen::MatrixXd(num_nodes_*dim_, num_nodes_*dim_);
        Eigen::VectorXd Q = Eigen::VectorXd(num_nodes_*dim_);
        for (int i=0; i<num_nodes_-1; i++)
        {
            double t = grid_.nodes_[i].coordinate;
            double tp = grid_.nodes_[i+1].coordinate;
            double h = tp-t;
            Eigen::VectorXd u = Eigen::VectorXd(sol_vec_.segment(dim_*i,dim_));
            Eigen::VectorXd up = Eigen::VectorXd(sol_vec_.segment(dim_*(i+1),dim_));

            Eigen::MatrixXd A = p_ode_->p_RhsGradYFunc(t, u);
            Eigen::MatrixXd Ap = p_ode_->p_RhsGradYFunc(tp, up);
            Eigen::MatrixXd I = Eigen::MatrixXd::Identity(dim_,dim_);
            Eigen::MatrixXd S = -(1.0/h)*I - 0.5*A;
            Eigen::MatrixXd R = (1.0/h)*I - 0.5*Ap;
            LeftMatrix.block(dim_*i,dim_*i,dim_,dim_) = S;
            LeftMatrix.block(dim_*i,dim_*(i+1),dim_,dim_) = R;
            Q.segment(dim_*i,dim_) = 0.5*(p_ode_->p_RhsFunc(tp,up)+p_ode_->p_RhsFunc(t,u))-(up-u)/h;
        }
        LeftMatrix.block(dim_*(num_nodes_-1),0,dim_,dim_) = Ba;
        LeftMatrix.block(dim_*(num_nodes_-1),dim_*(num_nodes_-1),dim_,dim_) = Bb;
        Q.segment(dim_*(num_nodes_-1),dim_) = beta;

        Eigen::VectorXd w = LeftMatrix.colPivHouseholderQr().solve(Q);

        sol_vec_ = sol_vec_+w;

        if (w.norm() < ERR_TOL) return;
    }
    return;
//    PopulateMatrix();
//    PopulateVector();
//    ApplyBoundaryConditions();
//    // solve
    //    WriteSolutionFile();
}

void BoundaryValueProblem::WriteSolutionFile()
{
    std::ofstream output_file(filename_.c_str());
    assert(output_file.is_open());
    for (int i=0; i<num_nodes_; i++)
    {
        double x = grid_.nodes_[i].coordinate;
        output_file << x << " " << sol_vec_(i) << "\n";
    }
    output_file.flush();
    output_file.close();
    std::cout << "Solution written to " << filename_ << std::endl;

}



//int main(int argc, char *argv[])
//{
//    DifferentialSystem ds(rhs, rhs_grad, bc, bc_grad1, bc_grad2, 0.0, 1.0);
//    BoundaryValueProblem bvp(&ds, 100,2);
//    bvp.Solve();
//    std::cout << bvp.sol_vec() << std::endl;;
//    return 0;
//}
