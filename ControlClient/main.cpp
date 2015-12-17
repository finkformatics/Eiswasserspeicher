#include <iostream>

#include "ControlClient.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <path/to/config_file>" << endl;
        return 1;
    }
    cout << "Control client started." << endl;
    ControlClient client(argv[1]);
    client.run();
    return 0;
}

