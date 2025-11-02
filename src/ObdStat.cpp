#include "ObdStat.hpp"

using namespace boost::asio;
using namespace std::chrono_literals;

namespace ljl
{
    ObdStat::ObdStat()
    {

    }

    void ObdStat::run()
    {
        try {

#if defined(_WIN32)
            std::string portName = "COM3"; // change as needed

#else
            std::string portName = "/dev/ttyUSB0"; // or /dev/ttyACM0

#endif
            ELM327 obd(portName);
            obd.init();

            while (true) 
            {
                std::string rpmResp = obd.requestPID("0C");
                double rpm = Utils::decodeRPM(rpmResp);

                std::string spdResp = obd.requestPID("0D");
                int speed = Utils::decodeSpeed(spdResp);

                std::cout << "Speed: " << speed << " km/h, RPM: " << rpm << std::endl;
                std::this_thread::sleep_for(1s);
            }

        } catch (std::exception& e) 
        {
            std::cerr << "=====OBDSTAT::RUN ERROR======\n" << e.what() << "\n";
        }
    }

    ObdStat::~ObdStat()
    {

    }
}