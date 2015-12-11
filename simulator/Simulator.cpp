#include "Simulator.h"

#include <iostream>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>

using namespace std;

Simulator::Simulator() : _port(55555), _control_server(_io_service, _port) {
    _io_service.run();
}

void Simulator::run() {
    cout << "Simulator started." << endl;
    boost::posix_time::seconds sleepTime(3);
    while (true) {
        cout << "Running..." << endl;
        boost::this_thread::sleep(sleepTime);
    }
}