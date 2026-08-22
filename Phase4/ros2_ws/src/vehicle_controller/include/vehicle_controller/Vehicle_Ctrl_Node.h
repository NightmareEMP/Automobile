#ifndef VEHICLE_CONTROLLER_NODE_HPP
#define VEHICLE_CONTROLLER_NODE_HPP

#include <rclcpp/rclcpp.hpp>

#include "vehicle_interface/msg/vehicle_command.hpp"
#include "vehicle_interface/msg/vehicle_feedback.hpp"
#include "vehicle_controller/msg/vehicle_pose.hpp"

class VehicleController : public rclcpp::Node
{
public:
    VehicleController();

private:
    void feedback_callback(
        const vehicle_interface::msg::VehicleFeedback::SharedPtr msg);

    void pose_callback(
        const vehicle_controller::msg::VehiclePose::SharedPtr msg);

    void control_loop();

private:
    // Receive feedback from vehicle_interface_node
    rclcpp::Subscription<
        vehicle_interface::msg::VehicleFeedback
    >::SharedPtr feedback_sub_;
    
    // Receive pose from the localization node
    rclcpp::Subscription<
        vehicle_controller::msg::VehiclePose
    >::SharedPtr pose_sub_;

    // Send command to vehicle_interface_node
    rclcpp::Publisher<
        vehicle_interface::msg::VehicleCommand
    >::SharedPtr command_pub_;

    // Run control periodically
    rclcpp::TimerBase::SharedPtr control_timer_;
    
    // Feedback ERPM from vehicle_interface_node
    int32_t actual_erpm_;

    int16_t desired_steering_;
    int16_t desired_throttle_;
    uint8_t desired_mode_;
};

#endif