#pragma once

#define _CRT_SECURE_NO_DEPRECATE // let unsafe asctime works for now

#include <boost/interprocess/ipc/message_queue.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "sharedData.hpp"

// I usually prefer using boost/std namespaces
// but in this case boost ones are too long
using namespace boost::interprocess;
using BoostQueue = message_queue;

class Sensor
{
public:
    Sensor(int dataGatherDelay);
    void run() const;
    void send() const;

private:
    bool internalSend(const shared::SensorData& data) const;
    shared::SensorData getData() const;

    uint32_t id_; // should be PID id which is 32 uint
    const int dataGatherDelay_;
};
