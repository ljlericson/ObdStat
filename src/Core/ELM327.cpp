#include "ELM327.hpp"

namespace Core
{
    ELM327::ELM327(const std::string& portName)
        : m_io(), m_port(m_io) 
    {
        uint32_t baud = 38400;
        using namespace boost::asio;
        m_port.open(portName);
        m_port.set_option(serial_port_base::baud_rate(baud));
        m_port.set_option(serial_port_base::character_size(8));
        m_port.set_option(serial_port_base::parity(serial_port_base::parity::none));
        m_port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
        m_port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
    }

    void ELM327::init() 
    {
        send("ATZ");   // Reset
        send("ATE0");  // Echo off
        send("ATL0");  // Linefeeds off
        send("ATS0");  // Spaces off
        send("ATH1");  // Headers on (optional, helps debugging)
        send("ATSP0"); // Auto protocol select
    }

    std::string ELM327::requestPID(const std::string& pid) 
    {
        std::string cmd = "01" + pid;
        return send(cmd);
    }

    std::string ELM327::send(const std::string& cmd)
    {
        using namespace boost::asio;
        using namespace std::chrono_literals;
        
        std::string request = cmd + "\r";
        write(m_port, buffer(request));
        std::this_thread::sleep_for(100ms);
        return readResponse();
    }

    std::string ELM327::readResponse() 
    {
        using namespace boost::asio;

        std::string response;
        char c;
        for (;;) 
        {
            read(m_port, buffer(&c, 1));
            if (c == '>') break; // ELM prompt
            response += c;
        }
        // strip CR/LF
        response.erase(remove(response.begin(), response.end(), '\r'), response.end());
        response.erase(remove(response.begin(), response.end(), '\n'), response.end());
        return response;
    }
}