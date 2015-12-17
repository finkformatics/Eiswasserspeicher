#ifndef CONTROLCLIENT_H
#define CONTROLCLIENT_H

#include <boost/asio.hpp>
#include <string>

using namespace std;
using boost::asio::ip::tcp;

class ControlClient {
public:
    ControlClient(const char* config_file);
    void run();
    void connect();
private:
    string _server_host;
    string _server_port;
    boost::asio::io_service _io_service;
    tcp::socket _socket;
    enum { max_length = 1024 };
};

#endif /* CONTROLCLIENT_H */

