#include "ObdStat.hpp"

namespace ljl
{
    ObdStat::ObdStat(int argc, char** argv)
    {
        if (argc < 3) 
        {
            std::cerr << "Usage: " << argv[0] << " <elm_file> <printer_ip>\n";
            std::exit(1);
        }

        mp_prinManager = std::make_shared<Manager::PrintManager>(argv[2]);
        mp_obd         = std::make_shared<Utils::ElmEmulator>(argv[1]);
        mp_statMonitor = Monitor::StatMonitor{mp_obd, mp_prinManager};

        if (!mp_obd) 
        {
            std::cerr << "Failed to initialize ElmEmulator\n";
            std::exit(1);
        }

        mp_obd->init();
    }

    void ObdStat::run()
    {  
        while (mp_obd->dataLeft()) 
        {
            using namespace std::chrono_literals;
            mp_prinManager->loop();
            mp_statMonitor.loop();
            
            std::this_thread::sleep_for(1s);
        }
    }

    ObdStat::~ObdStat()
    {

    }
}
