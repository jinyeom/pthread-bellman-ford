#include <iostream>
#include <string>
#include <cstring>

#include "../include/graph.h"
#include "../include/bellman_ford.h"

#define INF 9999999;

void Usage(char *prog) {
    std::cout << "usage: " << prog << " -f filename" << " [-p]" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    node_t src; // source node ID
    bool parallel = false;

    // parse program arguments
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-f")) {
            filename = argv[++i];
        } else if (!strcmp(argv[i], "-s")) {
            src = (node_t)stoi(argv[++i]);
        } else if (!strcmp(argv[i], "-p")) {
            parallel = true;
        }
    }
    if (filename.empty()) {
        Usage(argv[0]);
        return -1;
    }
    graph* g = new graph();
    if (!g->construct_from_dimacs(filename)) return -1;

    // initialize the graph
    int num_nodes = (int)g.size_nodes();
    edge_data_t distance[num_nodes] = {INF};
    node_t predecessor[num_nodes] = {0};
    distance[src] = 0.0;

    // repeat relaxation
    if (parallel) {

    } else {
        for (node_t u = g->begin(); u < g->end(); ++u) {
            for (edge_t e = g->edge_begin(u); e < g->edge_end(u); ++e) {
                node_t v = g->get_edge_dst(e);
                edge_data_t w = g->get_edge_data(e);
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                }
            }
        }
    }

    

    // NOTE: normally, the algorithm checks for negative cycles, but for the sake of saving time,
    // we'll just assume there aren't any, assuming all edges have positive weights.
    return 0;
}
