#include <iostream>
#include <string>
#include <cstring>

#include "../include/graph.h"
#include "../include/bellman_ford.h"

void Usage(char *prog) {
    std::cout << "usage: " << prog << " -f filename" << " [-p]" << std::endl;
}

int main(int argc, char* argv[]) {
    std::string filename;
    bool parallel = false;
    // parse program arguments
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-f")) {
            filename = argv[++i];
        } else if (!strcmp(argv[i], "-p")) {
            parallel = true;
        }
    }
    if (filename.empty()) {
        Usage(argv[0]);
        return -1;
    }
    BellmanFord* bf = new BellmanFord();
    

    return 0;
}