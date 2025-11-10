#pragma once
#include <chrono>

namespace Utils
{
    class Timer 
    {
    public:
        
        void start();
        
        void stop();

        operator bool();

        float sinceStarted() const;

    private:
        std::chrono::high_resolution_clock::time_point m_start;
        bool m_started;
    };
}