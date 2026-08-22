#include "vehicle_interface/Vehicle_Interface_Node.h"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto car = std::make_shared<Car>();

    if (!car->Start()) {
        RCLCPP_ERROR(car->get_logger(), "Failed to start vehicle interface");
        rclcpp::shutdown();
        return 1;
    }

    rclcpp::spin(car);

    car->Stop();
    rclcpp::shutdown();

    return 0;
}