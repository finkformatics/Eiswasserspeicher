#include "ControlClient.h"

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace po = boost::program_options;

ControlClient::ControlClient(const char* config_file) : _socket(_io_service) {
    cout << "Starting control client" << endl;
    po::options_description desc("Parameters");
    desc.add_options()
        ("server.host", po::value<string>(&_server_host), "server host")
        ("server.port", po::value<string>(&_server_port), "server port")
        ("options.power.min", po::value<int>(&_option_power_min), "minimum power");
    po::variables_map vm;
    std::ifstream file(config_file, std::ifstream::in);
    cout << "Reading program parameters" << endl;
    po::store(po::parse_config_file(file, desc), vm);
    file.close();
    po::notify(vm);
    connect();
}

ControlClient::~ControlClient() {
    _socket.close();
}

void ControlClient::connect() {
    cout << "Trying to connect to control server" << endl;
    _io_service.run();
    tcp::resolver resolver(_io_service);
    tcp::resolver::query query(tcp::v4(), _server_host, _server_port);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::connect(_socket, iterator);
    cout << "Connected" << endl;
}

void ControlClient::run() {
    cout << "Control client started" << endl;
    for (;;) {
        try {
            string choice = menu();
            if (choice == "NONE") {
                continue;
            } else if (choice == "EXIT") {
                break;
            }
            cout << "Sending command: " << choice << endl;;
            boost::asio::write(_socket, boost::asio::buffer(choice.c_str(), choice.length()));

            // 3 hardcoded
            char reply[3];
            size_t reply_length = boost::asio::read(_socket, boost::asio::buffer(reply, 3));
            cout << "Server replied: ";
            cout.write(reply, reply_length);
            cout << endl;
        } catch (exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
    cout << "Closing control client" << endl;
    delete this;
}

string ControlClient::menu() {
    cout << "You have the following options:" << endl;
    cout << "[1] ON" << endl;
    cout << "[2] OFF" << endl;
    cout << "[X] Exit" << endl;
    cout << "Your choice: " << endl;
    string choice;
    cin >> choice;
    if (choice == "X" || choice == "x") {
        return "EXIT";
    }
    char* choiceCString = (char*)choice.c_str();
    long int choiceInt = strtol(choiceCString, &choiceCString, 10);
    if (choiceInt == 1) {
        return "ON";
    }
    if (choiceInt == 2) {
        return "OFF";
    }
    cerr << "Option not supported!" << endl;
    return "NONE";
}

