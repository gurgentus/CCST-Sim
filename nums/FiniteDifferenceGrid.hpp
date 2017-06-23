#ifndef FINITEDIFFERENCESGRID
#define FINITEDIFFERENCESGRID

#include "Eigen/Dense"
#include <vector>
#include "BoundaryConditions.hpp"
#include "Node.hpp"

class FiniteDifferenceGrid
{
public:
    friend class BoundaryValueProblem;  // gives access to the nodes
private:
    std::vector<Node> nodes_;
public:
    FiniteDifferenceGrid(int num_nodes, double t_min, double t_max);
};

#endif
