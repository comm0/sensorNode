#pragma once

#include <random>
#include <stdint.h>
#include <time.h>

// There should be only one existance of that class
// for simplicity it has been duplicated among all
// projects where its beign used.
// It also contains some helper functions

namespace shared
{
namespace constant
{
    const auto MAX_QUE_MSG = 100;
    const auto QUEUE_NAME = "que1";
    const unsigned int NO_PRIORITY = 0;
}

    struct SensorData
    {
        uint32_t id; // DWORD is 32b uint
        int8_t temp;
        uint8_t moisture; // percentages
        std::time_t time;
    };
}