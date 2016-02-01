#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <boost/asio.hpp>

class TcpSession;

#include "Configuration.h"
#include "Simulator.h"

using boost::asio::ip::tcp;

class TcpSession {
public:
    TcpSession(Configuration* config, boost::asio::io_service& io_service, Simulator* simulator);
    virtual ~TcpSession();
    tcp::socket& socket();
    void start();
private:
    void run();
    void handle_read(size_t bytes_transferred, const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error);

    Configuration* config;
    tcp::socket _socket;
    enum { max_length = 1024 };
    char data[max_length];
    Simulator* simulator;
};

#endif /* TCPSESSION_H */