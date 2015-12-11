#ifndef TCPSESSION_H
#define	TCPSESSION_H

#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpSession {
public:
    TcpSession(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start();
private:
    void run();
    void handle_read(size_t bytes_transferred);
    void handle_write();
    
    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];
};

#endif	/* TCPSESSION_H */

