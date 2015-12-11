#ifndef CONTROLSERVER_H
#define	CONTROLSERVER_H

#include <boost/asio.hpp>
#include "TcpSession.h"

using boost::asio::ip::tcp;

class ControlServer {
public:
    ControlServer(boost::asio::io_service& io_service, short port);
private:
    void start_pairing();
    void handle_accept(TcpSession* new_session, const boost::system::error_code& error);
    
    boost::asio::io_service& _io_service;
    tcp::acceptor _acceptor;
};

#endif	/* CONTROLSERVER_H */

