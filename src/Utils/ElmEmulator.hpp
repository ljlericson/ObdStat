#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace Utils
{
    class ElmEmulator
    {
    public:
        static constexpr const char* ENG_COOLENT_TEMP_PID = "0105";
        static constexpr const char* ENG_WORK_PID = "0104";
        static constexpr const char* ENG_RUN_TIME_PID = "011F";
        static constexpr const char* VEC_SPEED_PID = "010D";
        static constexpr const char* VEC_FUEL_LVL_PID = "012F";

        ElmEmulator(const std::string& fpath);

        bool dataLeft();

        void init();

        double requestPID(const char* pid);
    private:
        // trying to emulate inefficiency in
        // elm327 lookup speed by having
        // massive inefficient vectors
        std::vector<double> m_engTemps;
        std::vector<double> m_engWorks;
        std::vector<double> m_vecSpeeds;
        std::vector<double> m_vecFuels;
        std::vector<size_t> m_engRunTimes;
    };
}