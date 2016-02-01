#ifndef CONTROLCLIENT_H
#define CONTROLCLIENT_H

#include <boost/asio.hpp>
#include <string>

using namespace std;
using boost::asio::ip::tcp;

class ControlClient {
public:
    ControlClient(const char* config_file);
    ~ControlClient();
    void run();
    void connect();
private:
    bool connected;
    string serverHost;
    string serverPort;
    string secretToken;
    boost::asio::io_service ioService;
    tcp::socket socket;
    enum { max_length = 1024 };
    string menu();
};

#endif /* CONTROLCLIENT_H */

