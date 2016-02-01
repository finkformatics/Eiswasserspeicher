#ifndef CONTROLSERVER_H
#define	CONTROLSERVER_H

#include <boost/asio.hpp>

class ControlServer;

#include "TcpSession.h"
#include "Simulator.h"

using boost::asio::ip::tcp;

class ControlServer {
public:
    ControlServer(Configuration* config, Simulator* simulator, boost::asio::io_service& io_service);
    void run();
private:
    void start_pairing();
    void handle_accept(TcpSession* new_session, const boost::system::error_code& error);
    
    Configuration* config;
    Simulator* simulator;
    boost::asio::io_service& ioService;
    tcp::acceptor acceptor;
};

#endif	/* CONTROLSERVER_H */

