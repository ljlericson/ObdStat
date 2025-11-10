#include "ElmEmulator.hpp"


namespace Utils
{
    void ElmEmulator::init()
    {
        // nothing exciting here
    }

    bool ElmEmulator::dataLeft()
    {
        if(m_engRunTimes.empty() ||
           m_engTemps.empty() ||
           m_engWorks.empty() || 
           m_vecSpeeds.empty() || 
           m_vecFuels.empty())
            return false;
        
        return true;
    }

    ElmEmulator::ElmEmulator(const std::string& fpath)
    {
        std::string line;
        std::ifstream file(fpath);

        if (!file.is_open()) 
        {
            std::cerr << "ERROR: Could not open file " << fpath << '\n';
            throw std::runtime_error("ElmEmulator: file not found");
        }


        double engTemp, engWork, vecFuel, vecSpeed;
        size_t engRunTime;

        while(std::getline(file, line))
        {

            std::stringstream s;
            s << line;
            s >> engTemp >> engWork >> vecFuel >> vecSpeed >> engRunTime;
            
            m_engRunTimes.push_back(engRunTime);
            m_engTemps.push_back(engTemp);
            m_engWorks.push_back(engWork);
            m_vecFuels.push_back(vecFuel);
            m_vecSpeeds.push_back(vecSpeed);
        }
    }

    double ElmEmulator::requestPID(const char* pid)
    {
        std::string _pid(pid);

        if(_pid == "ENG_COOLENT_TEMP_PID")
        {
            double val = m_engTemps[0];
            m_engTemps.erase(m_engTemps.begin());
            return val;
        }
        else if(_pid == "ENG_WORK_PID")
        {
            double val = m_engWorks[0];
            m_engWorks.erase(m_engWorks.begin());
            return val;
        }
        else if(_pid == "ENG_RUN_TIME_PID")
        {
            double val = m_engRunTimes[0];
            m_engRunTimes.erase(m_engRunTimes.begin());
            return val;
        }
        else if(_pid == "VEC_SPEED_PID")
        {
            double val = m_vecSpeeds[0];
            m_vecSpeeds.erase(m_vecSpeeds.begin());
            return val;
        }
        else if(_pid == "VEC_FUEL_LVL_PID")
        {
            double val = m_vecFuels[0];
            m_vecFuels.erase(m_vecFuels.begin());
            return val;
        }
    }
}
