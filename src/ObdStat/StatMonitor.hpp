#pragma once
#include <iostream>
#include <memory>

#include "../Core/ELM327.hpp"
#include "../Utils/Timer.h"
#include "../Vender/include/ljl/Stat.hpp"
#include "PrintManager.hpp"
#include "../Utils/ElmEmulator.hpp"

namespace Monitor
{
    class StatMonitor
    {
    public:
        StatMonitor() = default;
        StatMonitor(const std::shared_ptr<Utils::ElmEmulator>& obd, 
                    const std::shared_ptr<Manager::PrintManager>& printManager);

        void loop();

    private:
        std::shared_ptr<Utils::ElmEmulator> mp_obd;
        std::shared_ptr<Manager::PrintManager> mp_printManager;
        Utils::Timer m_timer;
        
        ljl::Stat::ContinuosSample m_engTemp;
        ljl::Stat::ContinuosSample m_engWork;
        ljl::Stat::ContinuosSample m_vecSpeed;
        double m_vecTopSpeed = 0.0;
        size_t m_engRunTime = 0;
    };
}