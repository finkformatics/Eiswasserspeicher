#include "ControlClient.h"

#include <boost/program_options.hpp>
#include <fstream>

namespace po = boost::program_options;

ControlClient::ControlClient(const char* config_file) : _socket(_io_service) {
    po::options_description desc("Parameters");
    desc.add_options()
        ("server.host", po::value<string>(&_server_host), "server_host")
        ("server.port", po::value<string>(&_server_port), "server_port");
    po::variables_map vm;
    std::ifstream file(config_file, std::ifstream::in);
    po::store(po::parse_config_file(file, desc), vm);
    file.close();
    po::notify(vm);
    connect();
}

void ControlClient::connect() {
    _io_service.run();
    tcp::resolver resolver(_io_service);
    tcp::resolver::query query(tcp::v4(), _server_host, _server_port);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::connect(_socket, iterator);
}

void ControlClient::run() {
    for (;;) {
        try {
            cout << "Enter command: ";
            char request[max_length];
            cin.getline(request, max_length);
            size_t request_length = strlen(request);
            boost::asio::write(_socket, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(_socket, boost::asio::buffer(reply, max_length));
            cout << "Server replied: ";
            cout.write(reply, reply_length);
            cout << endl;
        } catch (exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
}

