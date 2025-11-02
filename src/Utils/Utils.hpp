#include <string>
#include <sstream>

namespace Utils
{
    // === Example PID decoders ===
    double decodeRPM(const std::string& hexResponse);

    int decodeSpeed(const std::string& hexResponse);
}