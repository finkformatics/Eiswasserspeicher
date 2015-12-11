#ifndef SIMULATOR_H
#define	SIMULATOR_H

#include <boost/asio.hpp>

#include "ControlServer.h"

class Simulator {
public:
    Simulator();
    void run();
private:
    void start_server();
    
    short _port;
    boost::asio::io_service _io_service;
    ControlServer _control_server;
};

#endif	/* SIMULATOR_H */

