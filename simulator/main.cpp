#include <iostream>

#include "Simulator.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <path/to/config_file>" << endl;
        return 1;
    }
    Simulator simulator(argv[1]);
    simulator.run();
    return 0;
}

