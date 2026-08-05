#include "Vehicle_Ctrl.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main()
{
    Car car;

    if (!car.Start("/dev/ttyTHS1", 115200)) {
        std::cerr << "Failed to start vehicle controller\n";
        return 1;
    }

    const std::vector<int16_t> servo_values{
        Car::CENTER,
        Car::FULL_RIGHT,
        Car::CENTER,
        Car::FULL_LEFT
    };

    const std::vector<int16_t> motor_values{
        1000,
        2000,
        1000,
        Car::FULL_STOP
    };

    std::size_t index = 0;

    while (car.IsRunning()) {
        car.SetSteering(servo_values[index]);
        car.SetThrottle(motor_values[index]);
        index = (index + 1) % servo_values.size();

        /*
         * This controls how often the test command changes.
         *
         * The TX thread still sends the current command at 10 Hz.
         * Here, each test command is kept for one second.
         */
        // Must less then JETSON_TIMEOUT_MS (STM32 code)
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    car.Stop();

    return 0;
}