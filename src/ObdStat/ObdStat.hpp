#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "../Core/ELM327.hpp"
#include "../Core/PrinterInterface.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Timer.h"
#include "PrintManager.hpp"

#include "../Vender/include/ljl/Stat.hpp"

namespace ljl
{
    class ObdStat
    {
    public:
        ObdStat();

        void run();

        ~ObdStat();

    private:
        Core::ELM327* m_obd = nullptr;
        Core::PrinterInterface* m_prinInterf = nullptr;
        Manager::PrintManager m_prinManager;


        // millage testing
        ljl::Stat::ContinuosSample m_testSample;
        ljl::Stat::ContinuosSample m_controlSample;
        Utils::Timer* m_testTimer = nullptr;
    };
}