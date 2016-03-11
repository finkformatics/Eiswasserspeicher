#include "TcpSession.h"

#include <boost/thread.hpp>
#include <sstream>
#include "Logger.h"

using namespace std;

TcpSession::TcpSession(Configuration* config, boost::asio::io_service& io_service, Simulator* simulator)
        : _socket(io_service) {
    this->simulator = simulator;
    this->config = config;
}

TcpSession::~TcpSession() {
    ostringstream oss;
    oss << "Closed connection to control client " << _socket.remote_endpoint().port();
    Logger::info(oss.str());
}

tcp::socket& TcpSession::socket() {
    return _socket;
}

void TcpSession::run() {
    boost::system::error_code ec;
    char auth[max_length];
    size_t bytes_transferred = _socket.read_some(boost::asio::buffer(auth, max_length), ec);
    if (!ec) {
        string token = auth;
        if (token == config->getSecretToken()) {
            ostringstream oss;
            oss << "Successfully paired with control client " << _socket.remote_endpoint().port();
            Logger::info(oss.str());
            boost::system::error_code ec;
            _socket.write_some(boost::asio::buffer("OK", 3), ec);
            handle_write(ec);
        } else {
            delete this;
        }
    } else {
        boost::system::error_code ec;
        _socket.write_some(boost::asio::buffer("NO", 3), ec);
        delete this;
    }
}

void TcpSession::start() { 
    boost::thread(boost::bind(&TcpSession::run, this));
}

void TcpSession::handle_read(size_t bytes_transferred, const boost::system::error_code& error) {
    if (!error) {
        string command = data;
        ostringstream oss;
        oss << "Control client " << _socket.remote_endpoint().port() << " sent command: '" << command << "'";
        Logger::debug(oss.str());
        simulator->command(command);
        boost::system::error_code ec;
        oss.str("");
        oss.clear();
        oss << "Writing ok to client " << _socket.remote_endpoint().port();
        Logger::debug(oss.str());
        _socket.write_some(boost::asio::buffer("OK", 3), ec);
        handle_write(ec);
    } else {
        delete this;
    }
}

void TcpSession::handle_write(const boost::system::error_code& error) {
    if (!error) {
        boost::system::error_code ec;
        size_t bytes_transferred = _socket.read_some(boost::asio::buffer(data, max_length), ec);
        handle_read(bytes_transferred, ec);
    } else {
        delete this;
    }
}
