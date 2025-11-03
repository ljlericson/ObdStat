#include "Utils.hpp"

namespace Utils
{
    double decodeRPM(const std::string& hexResponse)
    {
        auto pos = hexResponse.find("410C");
        if (pos == std::string::npos || pos + 8 > hexResponse.size()) return -1;

        uint32_t A = std::stoul(hexResponse.substr(pos + 4, 2), nullptr, 16);
        uint32_t B = std::stoul(hexResponse.substr(pos + 6, 2), nullptr, 16);

        return ((A * 256.0) + B) / 4.0;
    }

    uint8_t decodeSpeed(const std::string& hexResponse) 
    {
        auto pos = hexResponse.find("410D");
        if (pos == std::string::npos) return -1;
        uint8_t A; // trying to keep overhead to a minimum
        std::stringstream ss;
        ss << std::hex << hexResponse.substr(pos + 4, 2);
        ss >> A;
        return A;
    }
}