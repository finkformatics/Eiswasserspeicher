#include <iostream>

#include <boost/thread.hpp>

#include "ControlServer.h"
#include "TcpSession.h"

using namespace std;

ControlServer::ControlServer(boost::asio::io_service& io_service, short port) 
      : _io_service(io_service), 
        _acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
    cout << "Control server started." << endl;
    cout << "Waiting for control client..." << endl;
    boost::thread(boost::bind(&ControlServer::start_pairing, this));
}

void ControlServer::start_pairing() {
    TcpSession* new_session = new TcpSession(_io_service);
    boost::system::error_code ec;
    _acceptor.accept(new_session->socket(), ec);
    handle_accept(new_session, ec);
}

void ControlServer::handle_accept(TcpSession* new_session, 
        const boost::system::error_code& error) {
    if (!error) {
        cout << "Control client asking for pairing..." << endl;
        new_session->start();
    } else {
        cout << error << endl;
        delete new_session;
    }
}