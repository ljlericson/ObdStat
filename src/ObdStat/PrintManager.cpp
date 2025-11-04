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
        if(m_events.find(e) == m_events.end())
            m_events.insert({e, val});
    }

    void PrintManager::loop()
    {
        // if(m_events.size() > 0)
        // {
        //     if(!m_eventPrintTimer)
        //     {

        //     }
        // }
        for(auto [e, val] : m_events)
            printEvent(e);
    }

    void PrintManager::printEvent(EventType e)
    {
        std::string data; // = m_printerInterface.getDataStr();
        // Initialize printer
        data += "\x1B\x40"; // ESC @ - reset printer

        int random = 0; //::rand() % 6;
        
        switch(e)
        {
            // Engine temp warnings
        case EventType::EngineCoolentOverheatInfo:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "============ INFO ============\n\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nEngine coolent tempreture high\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nAdvise break where next possible\n[VALUE]: \n";
            data += m_events.at(e);
            data += " C\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::EngineCoolentOverheatUrgent:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========== WARNING ==========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nEngine coolent tempreture high\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nPULL OVER WHERE SAFE\nTURN OFF AC\nTURN ON HEAT TO FULL BLAST\n[VALUE]: \n";
            data += m_events.at(e);
            data += " C\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::EngineCoolentUnderheat:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "============ INFO ============\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nEngine coolent tempreture low\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nAvoid high stress driving\n[VALUE]: \n";
            data += m_events.at(e);
            data += " C\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        // Engine work warnings
        case EventType::EngineOverworkTimeInfo:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "============ INFO ============\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nEngine work high for long time\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nAdvise slow down or less power\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::EngineOverworkTimeUrgent:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========== WARNING ==========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nEngine work high for long time\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nREDUCE ENGINE POWER\nENGINE DAMAGE POSSIBLE\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
            // Fuel
        case EventType::FuelLowInfo:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "============ INFO ============\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nFuel Low\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nAdvise refuel when possible\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::FuelLowUrgent:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========== WARNING ==========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nFuel very Low\n\x1B\x2D\x01[STATUS]\x1B\x2D\x00:\nAdvise pull over where safe\nAA phone: 0800 500 222\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
            // Recomendations
        case EventType::RecommendBreakDistanceTravelled:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========= Recommend =========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nBreak recommended\nDistance travelled is high\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::RecommendBreakEngineRunTime:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========= Recommend =========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nBreak recommended\nEngine run time is high\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
        case EventType::RecommendGenExternalAirTemp:
            // Bold + double height & width
            data += "\x1B\x21\x38";
            data += "========= Recommend =========\n";
            data += "\x1B\x21\x00";
            data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nKeep heater on\nExternal air temp low\n[VALUE]: \n";
            data += m_events.at(e);
            data += "%\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            break;
            // Easter eggs
        case EventType::RandomFact:
            // Bold + double height & width
            switch(random)
            {
            case 0:
                data += "\x1B\x21\x38";
                data += "========= Random fact =========\n";
                data += "\x1B\x21\x00";
                data += "\x1B\x2D\x01[MESSAGE]\x1B\x2D\x00:\nJulius Caesar once said,\nIt is easier to find men who\nwill volunteer to die than to\nwill volunteer to die than to\nfind those who are willing\nto endure pain with patience.\n";
                data += "\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
            }
            break;
        case EventType::ScaryMessage: // life's full of fun surprises
            switch(random)
            {
            case 0:
                data += "\x1B\x21\x38";
                data += "======= CRITICAL DANGER ======\n";
                data += "\x1B\x21\x00";
                data += "Do you feel safe?";
                data += "\n\n\x1B\x21\x38==============================\n\n\x1D\x56\x00";
                break;
            }
            break;
            // Standard
        case EventType::DriveOver:
            break;
        case EventType::DriveStarted:
            break;
        }

        std::ofstream file("text.txt");
        file << data;
        file.close();
        // m_printerInterface.send();
        // data.clear();
    }

}