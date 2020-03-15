#include "sensor.hpp"

namespace
{
int getRandomUniformVal(const int min, const int max)
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(e1);
}
}

void Sensor::run() const
{
    while (true)
    {
        internalSend(getData());
        std::this_thread::sleep_for(
            std::chrono::milliseconds(dataGatherDelay_));
    }
}

void Sensor::send() const
{
    internalSend(getData());
}

bool Sensor::internalSend(const shared::SensorData& data) const
{
    // Logger should be put into separate object
    std::cout << "Sending new data: " <<
        "Sensor id: " << data.id << " \n" <<
        "temperature [C]: " << static_cast<int16_t>(data.temp) << " \n" <<
        "moisture [%]: " << unsigned(data.moisture) << " \n" <<
        "time : " << std::asctime(std::localtime(&data.time)) << " \n";

    try
    {
        BoostQueue boostQueue(open_only, shared::constant::QUEUE_NAME);
        return boostQueue.try_send(
            &data,
            sizeof(data),
            shared::constant::NO_PRIORITY);
    }
    catch (interprocess_exception & ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return false;
}

shared::SensorData Sensor::getData() const
{
    return shared::SensorData({
        id_,
        static_cast<int8_t>(getRandomUniformVal(-30, 30)),
        static_cast<uint8_t>(getRandomUniformVal(0, 100)),
        std::time(nullptr)});
}

Sensor::Sensor(int dataGatherDelay) :
    // wanted to initialize id_ with process PID but
    // end up with problem with windows.h library
    id_(getRandomUniformVal(1, 1000)),
    dataGatherDelay_(dataGatherDelay)
{
    std::cout << "Sensor " << id_ << " created\n";
}