#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include "ELM327.hpp"
#include "Utils/Utils.hpp"

namespace ljl
{
    class ObdStat
    {
    public:
        ObdStat();

        void run();

        ~ObdStat();

    private:
        

    };
}