#include "ObdStat.hpp"

namespace ljl
{
    ObdStat::ObdStat()
        : m_prinManager("hello")
    {

    }

    void ObdStat::run()
    {
        try 
        {

#if defined(_WIN32)
            std::string portName = "COM3"; // change as needed

#else
            std::string portName = "/dev/ttyUSB1"; // or /dev/ttyACM0

#endif
            // m_obd = new Core::ELM327(portName);
            // m_obd->init();
            

            // m_prinInterf->getDataStr() = "HELLO WORLD!\nThis is a test of the printer\nDoes new line work?\nWhat about $p&cial ch@r@cters?\n";
            // m_prinInterf->send();

            m_prinManager.newEvent(Manager::PrintManager::EventType::EngineCoolentOverheatInfo, 1.0);
            m_prinManager.loop();

            // while (true) 
            // {
            //     using namespace std::chrono_literals;

            //     std::string rpmResp = m_obd->requestPID("0C");
            //     double rpm = Utils::decodeRPM(rpmResp);

            //     std::string spdResp = m_obd->requestPID("0D");
            //     int speed = Utils::decodeSpeed(spdResp);

            //     std::cout << "Speed: " << speed << " km/h, RPM: " << rpm << std::endl;
            //     std::this_thread::sleep_for(1s);
            // }

            

        } catch (std::exception& e) 
        {
            std::cerr << "=====OBDSTAT::RUN ERROR======\n" << e.what() << "\n";
        }
    }

    ObdStat::~ObdStat()
    {

    }
}
