#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <boost/asio.hpp>

class TcpSession;

#include "Simulator.h"

using boost::asio::ip::tcp;

class TcpSession {
public:
    TcpSession(boost::asio::io_service& io_service, Simulator* simulator);
    virtual ~TcpSession();
    tcp::socket& socket();
    void start();
private:
    void run();
    void handle_read(size_t bytes_transferred, const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error);
    
    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];
    Simulator* simulator;
};

#endif /* TCPSESSION_H */