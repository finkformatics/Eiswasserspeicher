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
            int choice = menu();
            if (choice == -1) {
                break;
            } else if (choice == -2) {
                continue;
            } else if (choice < 0 || (choice > 0 && choice < _option_power_min) || choice > 100) {
                cerr << "Minimum percentage power is " << _option_power_min << "%!" << endl;
                continue;
            }
            string request;
            char request_char_arr[max_length];
            sprintf(request_char_arr, "CMD:POWER:%03d#", choice);
            request += request_char_arr;
            cout << "Sending command: " << request << endl;;
            boost::asio::write(_socket, boost::asio::buffer(request.c_str(), request.length()));

            char reply[max_length];
            size_t reply_length = boost::asio::read(_socket, boost::asio::buffer(reply, max_length));
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

int ControlClient::menu() {
    cout << "You have the following options:" << endl;
    cout << "[1] ON" << endl;
    cout << "[2] OFF" << endl;
    cout << "[3] Percentage Power" << endl;
    cout << "[X] Exit" << endl;
    cout << "Your choice: " << endl;
    string choice;
    cin >> choice;
    if (choice == "X" || choice == "x") {
        return -1;
    }
    char* choiceCString = (char*)choice.c_str();
    long int choiceInt = strtol(choiceCString, &choiceCString, 10);
    if (choiceInt == 1) {
        return 100;
    }
    if (choiceInt == 2) {
        return 0;
    }
    if (choiceInt == 3) {
        cout << "Provide a percentage power between " << _option_power_min << " and 100: ";
        string input;
        cin >> input;
        char* inputCString = (char*)input.c_str();
        int percentage = strtol(inputCString, &inputCString, 10);
        return percentage;
    }
    cerr << "Option not supported!" << endl;
    return -2;
}

