#ifndef BOUNDARYVALUEPROBLEM
#define BOUNDARYVALUEPROBLEM

#include "Eigen/Dense"
#include "DifferentialSystem.hpp"
#include "FiniteDifferenceGrid.hpp"
#include "Node.hpp"

class BoundaryValueProblem
{
private:
    int num_nodes_;  // number of grid nodes
    int dim_;  // dimension of the system
    FiniteDifferenceGrid grid_;  // pointer to a grid

    DifferentialSystem* p_ode_;  // pointer to a system to solve
    Eigen::VectorXd sol_vec_; // pointer to the solution vector
    std::string filename_;  // allow the user to specify the output file or use a default name

    static constexpr double ERR_TOL = 1e-4;
    static const int MAX_ITER = 100;

public:
    BoundaryValueProblem(DifferentialSystem *p_ode, int num_nodes, int dim);

    void set_filename(const std::string& name)
    {
        filename_ = name;
    }
    void Solve();
    double Step(int i);
    void WriteSolutionFile();
    Eigen::VectorXd sol_vec() const
    {
        return sol_vec_;
    }
};

#endif
