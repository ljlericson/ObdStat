#include "PrintManager.hpp"

namespace Manager
{
    PrintManager::PrintManager(const std::string& printerPort)
        // : m_printerInterface(printerPort)
    {
        std::cout << "INFO: Print system initialised...\n";
    }

    void PrintManager::newEvent(EventType e, double val)
    {
        for(auto [event, val] : m_events)
        {
            if(e == event)
                return;
        }
        m_events.push_back({e, val});
    }

    void PrintManager::loop()
    {
        std::cout << "HERE";
        if(m_events.size() > 0)
        {
            if(!m_eventPrintTimer)
            {
                m_eventPrintTimer.start();
                auto [key, val] = m_events[0];
                this->printEvent(key, val);

                m_events.erase(m_events.begin());
            }
            else if(m_eventPrintTimer && m_eventPrintTimer.sinceStarted() > 5000)
            {
                m_eventPrintTimer.stop();
            }
        }
    }

    void PrintManager::printEvent(EventType e, double val)
    {
        std::string data; // = m_printerInterface.getDataStr();
        // Initialize printer
        data += "\x1B\x40"; // ESC @ - reset printer

        int random = 0; //::rand() % 6;
        
        switch(e)
        {
                // === Engine temp warnings ===
        case EventType::EngineCoolentOverheatInfo:
        {
            data += "\x1B\x40"; // reset
            data += "\x1B\x21\x11"; // bold + double height/width
            data += "============ INFO ============\r\n\r\n";
            data += "\x1B\x21\x00"; // reset

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Engine coolant temperature high\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Advise break where next possible\r\n";

            data += "[VALUE]: ";
            data += val;
            data += " C\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03"; // feed
            data += "\x1D\x56\x00"; // cut
        }
        break;

        case EventType::EngineCoolentOverheatUrgent:
        {
            data += "\x1B\x40"; // reset
            data += "\x1B\x21\x11";
            data += "========== WARNING ==========\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Engine coolant temperature high\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "PULL OVER WHERE SAFE\r\nTURN OFF AC\r\nTURN ON HEAT TO FULL BLAST\r\n";

            data += "[VALUE]: ";
            data += val;
            data += " C\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        case EventType::EngineCoolentUnderheat:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "============ INFO ============\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Engine coolant temperature low\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Avoid high stress driving\r\n";

            data += "[VALUE]: ";
            data += val;
            data += " C\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        // === Engine work warnings ===
        case EventType::EngineOverworkTimeInfo:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "============ INFO ============\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Engine work high for long time\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Advise slow down or less power\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        case EventType::EngineOverworkTimeUrgent:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "========== WARNING ==========\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Engine work high for long time\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "REDUCE ENGINE POWER\r\nENGINE DAMAGE POSSIBLE\r\n";

            data += "\x1B\x2D\x01"; data += "[VALUE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        // === Fuel warnings ===
        case EventType::FuelLowInfo:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "============ INFO ============\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Fuel Low\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Advise refuel when possible\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        case EventType::FuelLowUrgent:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "========== WARNING ==========\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Fuel very Low\r\n";

            data += "\x1B\x2D\x01"; data += "[STATUS]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Advise pull over where safe\r\nAA phone: 0800 500 222\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        // === Recommendations ===
        case EventType::RecommendBreakDistanceTravelled:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "========= Recommend =========\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Break recommended\r\nDistance travelled is high\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        case EventType::RecommendBreakEngineRunTime:
        {
            data += "\x1B\x40";
            data += "\x1B\x21\x11";
            data += "========= Recommend =========\r\n";
            data += "\x1B\x21\x00";
            // data += "\x1B\x2D\x00";
            data += "\x1B\x2D\x01"; data += "[MESSAGE]:"; data += "\x1B\x21\x00"; //data += ":\r\n";
            data += "Break recommended\r\nEngine run time is high\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        case EventType::RecommendGenExternalAirTemp:
        {
            data += "\x1B\x40"; // reset printer
            data += "\x1B\x21\x11";
            data += "========= Recommend =========\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
            data += "Keep heater on\r\nExternal air temp low\r\n";

            data += "[VALUE]: ";
            data += val;
            data += "%\r\n\r\n";

            data += "\x1B\x21\x11";
            data += "==============================\r\n";
            data += "\x1B\x21\x00";

            data += "\x1B\x64\x03";
            data += "\x1D\x56\x00";
        }
        break;

        // === Easter eggs ===
        case EventType::RandomFact:
        {
            switch(random)
            {
                case 0:
                    data += "\x1B\x40";
                    data += "\x1B\x21\x11";
                    data += "========= Random fact =========\r\n";
                    data += "\x1B\x21\x00";

                    data += "\x1B\x2D\x01"; data += "[MESSAGE]"; data += "\x1B\x2D\x00"; data += ":\r\n";
                    data += "Julius Caesar once said,\r\nIt is easier to find men who\r\nwill volunteer to die than to\r\nfind those who are willing\r\nto endure pain with patience.\r\n";

                    data += "\r\n\r\n\x1B\x21\x11";
                    data += "==============================\r\n\r\n";
                    data += "\x1B\x21\x00";

                    data += "\x1B\x64\x03";
                    data += "\x1D\x56\x00";
                    break;
            }
        }
        break;

        case EventType::ScaryMessage:
        {
            switch(random)
            {
                case 0:
                    data += "\x1B\x40";
                    data += "\x1B\x21\x11";
                    data += "======= CRITICAL DANGER ======\r\n";
                    data += "\x1B\x21\x00";

                    data += "\r\nDo you feel safe?\r\n";

                    data += "\x1B\x21\x11";
                    data += "==============================\r\n\r\n";
                    data += "\x1B\x21\x00";

                    data += "\x1B\x64\x03";
                    data += "\x1D\x56\x00";
                    break;
            }
        }
        break;
        case EventType::DriveOver:
            break;
        case EventType::DriveStarted:
            break;
        }

        std::cout << "FILE GENERATED\n";
        std::ofstream file("text.txt", std::ios::binary);
        file << data.data();
        file.close();
        // m_printerInterface.send();
        // data.clear();
    }

}