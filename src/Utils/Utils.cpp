#include "Utils.hpp"

namespace Utils
{
    // === Example PID decoders ===
    double decodeRPM(const std::string& hexResponse) 
    {
        // expects "410C1AF8"
        auto pos = hexResponse.find("410C");
        if (pos == std::string::npos) return -1;
        unsigned A, B;
        std::stringstream ss;
        ss << std::hex << hexResponse.substr(pos + 4);
        ss >> A >> B;
        return ((A * 256) + B) / 4.0;
    }

    int decodeSpeed(const std::string& hexResponse) 
    {
        auto pos = hexResponse.find("410D");
        if (pos == std::string::npos) return -1;
        unsigned A;
        std::stringstream ss;
        ss << std::hex << hexResponse.substr(pos + 4, 2);
        ss >> A;
        return A;
    }
}