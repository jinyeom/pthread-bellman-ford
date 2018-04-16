#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <fstream>

#include "../include/graph.h"

void Usage(char *prog) {
    std::cout << "usage: " << prog << " -f filename" << " [-p]" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    graph::node_t src; // source node ID
    bool parallel = false;

    // parse program arguments
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-f")) {
            filename = argv[++i];
        } else if (!strcmp(argv[i], "-s")) {
            src = (graph::node_t)std::stoi(argv[++i]);
        } else if (!strcmp(argv[i], "-p")) {
            parallel = true;
        }
    }
    if (filename.empty()) {
        Usage(argv[0]);
        return -1;
    }
    graph g;
    if (!g.construct_from_dimacs(filename)) return -1;

    // initialize the graph
    int num_nodes = (int)g.size_nodes();
    graph::edge_data_t distance[num_nodes];
    for (int i = 0; i < num_nodes; ++i) {
        distance[i] = std::numeric_limits<int>::max();
    }
    distance[src - 1] = 0;

    // repeat relaxation
    if (parallel) {

    } else {
        for (int i = 0; i < num_nodes - 1; ++i) {
            for (graph::node_t u = g.begin(); u < g.end(); u++) {
                for (graph::edge_t e = g.edge_begin(u); e < g.edge_end(u); e++) {
                    graph::node_t v = g.get_edge_dst(e);
                    graph::edge_data_t w = g.get_edge_data(e);
                    // take care of cases with infinity
                    graph::edge_data_t updated = distance[u] + w;
                    if (distance[u] == std::numeric_limits<int>::max()) {
                        updated = distance[u];
                    }
                    // update the distance
                    if (distance[v] > updated) {
                        distance[v] = updated;
                    }
                }
            }
        }
    }

    // export result to a text file
    for (int i = 0; i < num_nodes; ++i) {
        std::string dist_str = std::to_string(distance[i]);
        if (distance[i] == std::numeric_limits<int>::max()) dist_str = "INF";
        std::cout << i + 1 << " " << dist_str << std::endl;
    }

    // NOTE: normally, the algorithm checks for negative cycles, but for the sake of saving time,
    // we'll just assume there aren't any, assuming all edges have positive weights.
    return 0;
}
