#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"

class BellmanFord {
public:
    bool InitGraph(const std::string filename);
    void Run(bool parallel);

private:
    graph* graph_;
    double distance[];
};

#endif
