#ifndef TCPSESSION_H
#define TCPSESSION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class ControlServer;

class TcpSession {
public:
    TcpSession(boost::asio::io_service& io_service, ControlServer* server);
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
    ControlServer* server;
};

#endif /* TCPSESSION_H */