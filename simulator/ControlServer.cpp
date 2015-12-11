#include <iostream>

#include "ControlServer.h"
#include "TcpSession.h"

using namespace std;

ControlServer::ControlServer(boost::asio::io_service& io_service, short port) 
      : _io_service(io_service), 
        _acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
    cout << "Control server started." << endl;
    cout << "Waiting for control client..." << endl;
    start_pairing();
}

void ControlServer::start_pairing() {
    TcpSession* new_session = new TcpSession(_io_service);
    _acceptor.async_accept(new_session->socket(), 
            boost::bind(&ControlServer::handle_accept, this, new_session, 
                boost::asio::placeholders::error));
}

void ControlServer::handle_accept(TcpSession* new_session, 
        const boost::system::error_code& error) {
    if (!error) {
        cout << "Control client asking for pairing..." << endl;
        new_session->start();
    } else {
        delete new_session;
    }
}