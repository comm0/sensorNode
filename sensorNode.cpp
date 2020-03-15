#include <thread>

#include "sensor.hpp"

const int SENSOR_DATA_GATHER_DELAY = 5000; // milliseconds

void detectClientInput(Sensor& sensor)
{
    while (std::cin.ignore())
    {
        std::cout << "User input detected, sending instant update\n";
        sensor.send();
    }
}

void sensorThread(Sensor& sensor)
{
    sensor.run();
}

// Program runs single sensor that sends data every defined interval
// in the meantime user can instant-update the data to main node by
// pressing enter during program execution
int main()
{
    Sensor sensor(SENSOR_DATA_GATHER_DELAY);
    
    std::thread sensorThread(&sensorThread, std::ref(sensor));
    std::thread clientThread(&detectClientInput, std::ref(sensor));

    clientThread.join();
    sensorThread.join();

    return 0;
}
