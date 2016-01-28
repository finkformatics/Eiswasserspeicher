#include "Simulator.h"

#include <iostream>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <string>

using namespace std;

Simulator::Simulator(const char* config_file) : config(config_file), 
        reservoir(&config) {
    controlServer = new ControlServer(this, ioService, config.getPort());
    ioService.run();
    controlServer->run();
}

void Simulator::run() {
    cout << "Simulator started." << endl;
    boost::posix_time::seconds sleepTime(1);
    while (true) {
        boost::this_thread::sleep(sleepTime);
        reservoir.step();
    }
}

void Simulator::command(char* cmd) {
    string str = cmd;
    if (str == "ON") {
        reservoir.enablePumps();
    } else if (str == "OFF") {
        reservoir.disablePumps();
    }
}