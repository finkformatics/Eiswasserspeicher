#include "TcpSession.h"

#include <boost/thread.hpp>

using namespace std;

TcpSession::TcpSession(boost::asio::io_service& io_service, ControlServer* server)
        : _socket(io_service) {
    this->server = server;
}

tcp::socket& TcpSession::socket() {
    return _socket;
}

void TcpSession::run() {
    size_t bytes_transferred = _socket.read_some(boost::asio::buffer(_data, max_length));
    handle_read(bytes_transferred);
}

void TcpSession::start() { 
    cout << "Successfully paired with control client." << endl;
    cout << "Starting control session." << endl;
    boost::thread(boost::bind(&TcpSession::run, this));
}

void TcpSession::handle_read(size_t bytes_transferred) {
    char* command;
    strncpy(command, _data, strlen(_data) - 1);
    cout << "Control client sent command: '" << command << "'" << endl;
    _socket.write_some(boost::asio::buffer(_data, bytes_transferred));
    handle_write();
}

void TcpSession::handle_write() { 
    cout << "Writing the same back to control client." << endl;
    size_t bytes_transferred = _socket.read_some(boost::asio::buffer(_data, max_length));
    handle_read(bytes_transferred);
}