#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

class ELM327 {
public:
    ELM327(const std::string& portName);

    void init();

    std::string requestPID(const std::string& pid);

    std::string send(const std::string& cmd);

private:
    std::string readResponse();

    boost::asio::io_context m_io;
    boost::asio::serial_port m_port;
};