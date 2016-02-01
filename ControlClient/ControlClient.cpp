#include "ControlClient.h"

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace po = boost::program_options;

ControlClient::ControlClient(const char* config_file) : socket(ioService) {
    connected = false;
    cout << "Starting control client" << endl;
    po::options_description desc("Parameters");
    desc.add_options()
        ("server.host", po::value<string>(&serverHost), "server host")
        ("server.port", po::value<string>(&serverPort), "server port")
        ("server.secret.token", po::value<string>(&secretToken), "server secret token");
    po::variables_map vm;
    std::ifstream file(config_file, std::ifstream::in);
    cout << "Reading program parameters" << endl;
    po::store(po::parse_config_file(file, desc), vm);
    file.close();
    po::notify(vm);
    connect();
}

ControlClient::~ControlClient() {
    socket.close();
}

void ControlClient::connect() {
    cout << "Trying to connect to control server" << endl;
    ioService.run();
    tcp::resolver resolver(ioService);
    tcp::resolver::query query(tcp::v4(), serverHost, serverPort);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    boost::asio::connect(socket, iterator);
            
    boost::asio::write(socket, boost::asio::buffer(secretToken.c_str(), secretToken.length()));
    char reply[2];
    boost::asio::read(socket, boost::asio::buffer(reply, 2));
    string rep = reply;
    if (rep == "OK") {
        cout << "Connected" << endl;
        connected = true;
    } else {
        cout << "Error" << endl;
    }
    
}

void ControlClient::run() {
    if (!connected) {
        delete this;
    }
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
            boost::asio::write(socket, boost::asio::buffer(choice.c_str(), choice.length()));

            char reply[2];
            size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, 2));
            cout << "Server replied: ";
            cout.write(reply, reply_length);
            cout << endl;
        } catch (exception& e) {
            cerr << "Exception: " << e.what() << endl;
            break;
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
        return "#ON";
    }
    if (choiceInt == 2) {
        return "OFF";
    }
    cerr << "Option not supported!" << endl;
    return "NONE";
}

