#include "vehicle_controller/Vehicle_Ctrl_Node.h"

#include <chrono>

using namespace std::chrono_literals;

static constexpr int16_t CENTER        = 1520;
static constexpr int16_t FULL_STOP     = 0;

VehicleController::VehicleController()
    : rclcpp::Node("vehicle_controller"),
      actual_erpm_(0),
      desired_steering_(CENTER),
      desired_throttle_(FULL_STOP),
      desired_mode_(1)
{   
    // Get erpm and related feedback from feedback topic
    feedback_sub_ =
        this->create_subscription<
            vehicle_interface::msg::VehicleFeedback>(
                "/vehicle_feedback",
                10,
                std::bind(
                    &VehicleController::feedback_callback,
                    this,
                    std::placeholders::_1));


     // Get erpm and related feedback from feedback topic
    pose_sub_ =
        this->create_subscription<
            vehicle_controller::msg::VehiclePose>(
                "/vehicle_pose",
                10,
                std::bind(
                    &VehicleController::pose_callback,
                    this,
                    std::placeholders::_1));
    // Publish desired steering, throttle, and mode to command topic
    command_pub_ =
        this->create_publisher<
            vehicle_interface::msg::VehicleCommand>(
                "/vehicle_command",
                10);

    control_timer_ =
        this->create_wall_timer(
            100ms,
            std::bind(
                &VehicleController::control_loop,
                this));
}

// Callback function to handle feedback messages
void VehicleController::feedback_callback(
    const vehicle_interface::msg::VehicleFeedback::SharedPtr msg)
{
    actual_erpm_ = msg->erpm;

    RCLCPP_INFO(
    this->get_logger(),
    "Received feedback: ERPM=%d current=%d duty=%d",
    msg->erpm,
    msg->motor_current_x10,
    msg->duty_x1000);
}

// Callback function to handle pose messages
void VehicleController::pose_callback(
    const vehicle_controller::msg::VehiclePose::SharedPtr msg)
{
    desired_steering_ = msg->steering;
    desired_throttle_ = msg->throttle;
    desired_mode_ = msg->mode;


    // RCLCPP_INFO(
    // this->get_logger(),
    // "Received CMD: Steering=%d Throttle=%d Mode=%d",
    // msg->steering,
    // msg->throttle,
    // msg->mode);
}

// Send the desired steering, throttle, and mode to the vehicle_interface_node
void VehicleController::control_loop()
{
    vehicle_interface::msg::VehicleCommand command_msg;

    command_msg.steering = desired_steering_;
    command_msg.throttle = desired_throttle_;
    command_msg.mode = desired_mode_;

    command_pub_->publish(command_msg);

    // RCLCPP_INFO(
    //     this->get_logger(),
    //     "Desired Steering = %d, Desired Throttle = %d, Desired Mode = %d",
    //     desired_steering_,
    //     desired_throttle_,
    //     desired_mode_);
}