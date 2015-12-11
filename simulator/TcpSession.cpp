#include "TcpSession.h"

#include <boost/thread.hpp>

using namespace std;

TcpSession::TcpSession(boost::asio::io_service& io_service)
        : _socket(io_service) {
    // Nothing to do
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
    cout << "Control client wrote: '" << _data << "'" << endl;
    _socket.write_some(boost::asio::buffer(_data, bytes_transferred));
    handle_write();
}

void TcpSession::handle_write() { 
    cout << "Writing the same back to control client." << endl;
    size_t bytes_transferred = _socket.read_some(boost::asio::buffer(_data, max_length));
    handle_read(bytes_transferred);
}