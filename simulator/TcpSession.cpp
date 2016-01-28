#include "TcpSession.h"

#include <boost/thread.hpp>

using namespace std;

TcpSession::TcpSession(boost::asio::io_service& io_service, ControlServer* server)
        : _socket(io_service) {
    this->server = server;
}

TcpSession::~TcpSession() {
    cout << "Closed connection to client " << _socket.remote_endpoint().port() << "." << endl;
}

tcp::socket& TcpSession::socket() {
    return _socket;
}

void TcpSession::run() {
    boost::system::error_code ec;
    size_t bytes_transferred = _socket.read_some(boost::asio::buffer(_data, max_length), ec);
    handle_read(bytes_transferred, ec);
}

void TcpSession::start() { 
    cout << "Successfully paired with control client " << _socket.remote_endpoint().port() << "." << endl;
    boost::thread(boost::bind(&TcpSession::run, this));
}

void TcpSession::handle_read(size_t bytes_transferred, const boost::system::error_code& error) {
    if (!error) {
        char* command;
        strncpy(command, _data, strlen(_data));
        cout << "Control client " << _socket.remote_endpoint().port() << " sent command: " << command  << endl;
        boost::system::error_code ec;
        _socket.write_some(boost::asio::buffer("OK\n", 3), ec);
        handle_write(ec);
    } else {
        delete this;
    }
}

void TcpSession::handle_write(const boost::system::error_code& error) {
    if (!error) {
        cout << "Writing ok to client " << _socket.remote_endpoint().port() << "." << endl;
        boost::system::error_code ec;
        size_t bytes_transferred = _socket.read_some(boost::asio::buffer(_data, max_length), ec);
        handle_read(bytes_transferred, ec);
    } else {
        delete this;
    }
}