#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "../Utils/Timer.h"
#include "../Core/PrinterInterface.hpp"

namespace Manager
{
    class PrintManager
    {
    public:
        enum class EventType
        {
            // Engine temp warnings
            EngineCoolentOverheatInfo,
            EngineCoolentOverheatUrgent,
            EngineCoolentUnderheat,
            // Engine work warnings
            EngineOverworkTimeInfo,
            EngineOverworkTimeUrgent,
            // Fuel
            FuelLowInfo,
            FuelLowUrgent,
            // Recomendations
            RecommendBreakDistanceTravelled,
            RecommendBreakEngineRunTime,
            RecommendGenExternalAirTemp,
            // Easter eggs
            RandomFact,
            ScaryMessage, // life's full of fun surprises
            // Standard
            DriveOver,
            DriveStarted
        };

        PrintManager(const std::string& printerPort);

        void newEvent(EventType e, double val);

        void loop();

    private:
        void printEvent(EventType e, double val);

        std::vector<std::pair<EventType, double>> m_events;
        Utils::Timer m_eventPrintTimer;
        // Core::PrinterInterface m_printerInterface;
    };
}