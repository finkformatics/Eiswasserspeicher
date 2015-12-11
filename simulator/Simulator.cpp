#include "Simulator.h"

Simulator::Simulator() : _port(55555), _control_server(_io_service, _port) {
    _io_service.run();
}

void Simulator::run() {
    // Implement it!
}