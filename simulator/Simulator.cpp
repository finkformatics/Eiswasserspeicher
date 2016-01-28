#include "Simulator.h"

#include <iostream>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>

using namespace std;

Simulator::Simulator(const char* config_file) : config(config_file), 
        controlServer(ioService, config.getPort()), 
        reservoir(&config) {
    ioService.run();
    controlServer.run();
}

void Simulator::run() {
    cout << "Simulator started." << endl;
    boost::posix_time::seconds sleepTime(5);
    while (true) {
        boost::this_thread::sleep(sleepTime);
        reservoir.step();
    }
}