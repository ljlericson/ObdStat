#include "Timer.h"

void Utils::Timer::start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

Utils::Timer::operator bool()
{
    return m_started;
}

float Utils::Timer::sinceStarted() const
{
    using namespace std::chrono;
    if(m_started)
        return duration_cast<duration<float, std::milli>>(high_resolution_clock::now() - m_start).count();
    
    return -1.0f;
}