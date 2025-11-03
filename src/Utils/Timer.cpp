#include "Timer.h"

Util::Timer::Timer()
    : m_start(std::chrono::high_resolution_clock::now()) { }

void Util::Timer::reset()
{
    m_start = std::chrono::high_resolution_clock::now();
}

float Util::Timer::sinceStarted() const
{
    using namespace std::chrono;
    return duration_cast<duration<float, std::milli>>(high_resolution_clock::now() - m_start).count();
}