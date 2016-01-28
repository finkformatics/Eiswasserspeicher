#ifndef CONTROLSERVER_H
#define	CONTROLSERVER_H

#include <boost/asio.hpp>

class ControlServer;

#include "TcpSession.h"
#include "Simulator.h"

using boost::asio::ip::tcp;

class ControlServer {
public:
    ControlServer(Simulator* simulator, boost::asio::io_service& io_service, short port);
    void run();
private:
    void start_pairing();
    void handle_accept(TcpSession* new_session, const boost::system::error_code& error);
    
    Simulator* simulator;
    boost::asio::io_service& _io_service;
    tcp::acceptor _acceptor;
};

#endif	/* CONTROLSERVER_H */

