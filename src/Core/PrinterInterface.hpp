#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

namespace Core
{
    class PrinterInterface
    {
    public:
        PrinterInterface(const std::string& portName);

        std::string& getDataStr();

        void data(const std::string& data);

        void send();

        operator bool();

    private:
        boost::asio::io_context m_io;
        boost::asio::serial_port m_port;
        std::string m_data;
        
    };
}