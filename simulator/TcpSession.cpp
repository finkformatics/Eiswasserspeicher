#include "TcpSession.h"

using namespace std;

TcpSession::TcpSession(boost::asio::io_service& io_service)
        : _socket(io_service) {
    // Nothing to do
}

tcp::socket& TcpSession::socket() {
    return _socket;
}

void TcpSession::start() {
    cout << "Successfully paired with control client." << endl;
    cout << "Starting control session." << endl;
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
            boost::bind(&TcpSession::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void TcpSession::handle_read(const boost::system::error_code& error,
        size_t bytes_transferred) {
    cout << "Control client wrote: '" << _data << "'" << endl; 
    if (!error) {
        cout << "Writing the same back to control client." << endl;
        boost::asio::async_write(_socket,
                boost::asio::buffer(_data, bytes_transferred),
                boost::bind(&TcpSession::handle_write, this,
                boost::asio::placeholders::error));
    } else {
        delete this;
    }
}

void TcpSession::handle_write(const boost::system::error_code& error) {
    if (!error) {
        _socket.async_read_some(boost::asio::buffer(_data, max_length),
                boost::bind(&TcpSession::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        delete this;
    }
}