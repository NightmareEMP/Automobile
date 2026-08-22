#include "rclcpp/rclcpp.hpp"
#include "vehicle_controller/Vehicle_Ctrl_Node.h"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto controller =
        std::make_shared<VehicleController>();

    rclcpp::spin(controller);

    rclcpp::shutdown();

    return 0;
}

