#include <cassert>
#include "FiniteDifferenceGrid.hpp"
#include "Node.hpp"

FiniteDifferenceGrid::FiniteDifferenceGrid(unsigned long num_nodes, double t_min, double t_max)
{
    double step_size = (t_max-t_min)/((double)(num_nodes-1));
    for (int i=0; i<num_nodes; i++)
    {
        Node node;
        node.coordinate = t_min+i*step_size;
        nodes_.push_back(node);
    }
    assert(nodes_.size() == num_nodes);
}




