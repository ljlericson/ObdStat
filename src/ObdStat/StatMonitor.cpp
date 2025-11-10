#include "StatMonitor.hpp"

namespace Monitor
{
    StatMonitor::StatMonitor(const std::shared_ptr<Utils::ElmEmulator>& obd, 
                             const std::shared_ptr<Manager::PrintManager>& printManager)
        : 
        mp_obd(obd), 
        mp_printManager(printManager) 
    {       }
    
    void StatMonitor::loop()
    {
        if(!m_timer)
            m_timer.start();

        // keeping it the average over 10 seconds
        // for propper detection
        else if(m_timer && m_timer.sinceStarted() > 10000)
        {
            m_engTemp = {};
            m_engWork = {};
        }
        std::cout << m_engTemp.getMean() << ' ' << m_engWork.getMean() << '\n';
        m_engTemp << mp_obd->requestPID(Utils::ElmEmulator::ENG_COOLENT_TEMP_PID);
        m_engWork << mp_obd->requestPID(Utils::ElmEmulator::ENG_WORK_PID);
        double vecSpeed = mp_obd->requestPID(Utils::ElmEmulator::VEC_SPEED_PID);

        if(vecSpeed > m_vecTopSpeed);
            m_vecTopSpeed = vecSpeed;

        if(m_engTemp.getMean() > 105)
            mp_printManager->newEvent(
                (m_engTemp.getMean() > 170) ? Manager::PrintManager::EventType::EngineCoolentOverheatUrgent 
                                            : Manager::PrintManager::EventType::EngineCoolentOverheatInfo, 
                m_engTemp.getMean());
            
        if(m_engWork.getMean() > 80)
            mp_printManager->newEvent(
                (m_engWork.getMean() > 90) ? Manager::PrintManager::EventType::EngineOverworkTimeInfo 
                                            : Manager::PrintManager::EventType::EngineOverworkTimeUrgent, 
                m_engWork.getMean());        
    }

}