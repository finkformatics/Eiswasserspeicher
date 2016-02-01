#include "ControlServer.h"
#include "Logger.h"

#include <iostream>

#include <boost/thread.hpp>

using namespace std;

ControlServer::ControlServer(Configuration* config, Simulator* simulator, boost::asio::io_service& io_service) 
      : ioService(io_service), 
        acceptor(io_service, tcp::endpoint(tcp::v4(), config->getPort())) {
    this->simulator = simulator;
    this->config = config;
}

void ControlServer::run() {
    Logger::info("Control server started, waiting for control client");
    boost::thread(boost::bind(&ControlServer::start_pairing, this));
}

void ControlServer::start_pairing() {
    TcpSession* new_session = new TcpSession(config, ioService, simulator);
    boost::system::error_code ec;
    acceptor.accept(new_session->socket(), ec);
    handle_accept(new_session, ec);
}

void ControlServer::handle_accept(TcpSession* new_session, 
        const boost::system::error_code& error) {
    if (!error) {
        Logger::debug("Control client asking for pairing");
        boost::thread(boost::bind(&TcpSession::start, new_session));
    } else {
        cout << error << endl;
        delete new_session;
    }
    start_pairing();
}