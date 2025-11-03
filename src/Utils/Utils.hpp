#include <string>
#include <sstream>

namespace Utils
{
    double decodeRPM(const std::string& hexResponse);

    // honestly if someone goes over 256 km/h they
    // deserve a medal
    uint8_t decodeSpeed(const std::string& hexResponse);
}