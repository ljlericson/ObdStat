#include "PrinterInterface.hpp"

namespace Core
{
    PrinterInterface::PrinterInterface(const std::string& portName)
            : m_io(), m_port(m_io)
    {
        m_port.set_option(boost::asio::serial_port_base::baud_rate(9600));
        m_port.set_option(boost::asio::serial_port_base::character_size(8));
        m_port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        m_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        m_port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
    }

    std::string& PrinterInterface::getDataStr()            { return m_data; }
    void PrinterInterface::data(const std::string& data)   { m_data = data; }

    void PrinterInterface::send()
    {
        using namespace boost;
        using namespace std::chrono_literals;

        asio::write(m_port, asio::buffer(m_data));
        std::this_thread::sleep_for(100ms);
    }
}