#include <string>

#include "../include/bellman_ford.h"
#include "../include/graph.h"

bool InitGraph(const std::string filename) {
    graph_ = new graph();
    if (!graph_->construct_from_dimacs(filename)) {
        std::cerr << "Failed to construct the argument graph" << std::endl;
        return false;
    }
    return true;
}

void BellmanFord::Run(bool parallel) {
    if (parallel) {

    } else {

    }
}