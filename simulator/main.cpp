/* 
 * File:   main.cpp
 * Author: lukas
 *
 * Created on 11. Dezember 2015, 07:54
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

enum {
    max_length = 1024
};

/*
 * 
 */
int main(int argc, char** argv) {
    try {
        if (argc != 3) {
            cerr << "Usage echoclient <host> <port>" << endl;
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        tcp::socket s(io_service);
        boost::asio::connect(s, iterator);

        cout << "Enter message: ";
        char request[max_length];
        cin.getline(request, max_length);
        size_t request_length = strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length));
        cout << "Reply is: ";
        cout.write(reply, reply_length);
        cout << endl;
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}

