#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <fstream>

#include "../Utils/Utils.hpp"
#include "../Utils/Timer.h"
#include "PrintManager.hpp"
#include "StatMonitor.hpp"
#include "../Core/ELM327.hpp"
#include "../Core/PrinterInterface.hpp"

#include "../Utils/ElmEmulator.hpp"

namespace ljl
{
    class ObdStat
    {
    public:
        ObdStat(int argc, char** argv);

        void run();

        ~ObdStat();

    private:
        Monitor::StatMonitor mp_statMonitor;
    
        std::shared_ptr<Manager::PrintManager> mp_prinManager;
        std::shared_ptr<Utils::ElmEmulator> mp_obd;
        std::shared_ptr<Core::PrinterInterface> mp_prinInt;
    };
}