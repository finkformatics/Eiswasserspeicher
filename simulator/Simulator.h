#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <boost/asio.hpp>
#include <string>

class Simulator;

#include "ControlServer.h"
#include "Configuration.h"
#include "Reservoir.h"

using namespace std;

class Simulator {
public:
    Simulator(const char* config_file);
    void run();
    void command(string cmd);
private:
    Configuration config;
    boost::asio::io_service ioService;
    ControlServer* controlServer;
    Reservoir reservoir;
    
    void start_server();
};

#endif	/* SIMULATOR_H */

