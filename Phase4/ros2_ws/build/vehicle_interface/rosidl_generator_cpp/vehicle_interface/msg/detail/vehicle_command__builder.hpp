// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interface:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_interface/msg/detail/vehicle_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_interface
{

namespace msg
{

namespace builder
{

class Init_VehicleCommand_mode
{
public:
  explicit Init_VehicleCommand_mode(::vehicle_interface::msg::VehicleCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_interface::msg::VehicleCommand mode(::vehicle_interface::msg::VehicleCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleCommand msg_;
};

class Init_VehicleCommand_throttle
{
public:
  explicit Init_VehicleCommand_throttle(::vehicle_interface::msg::VehicleCommand & msg)
  : msg_(msg)
  {}
  Init_VehicleCommand_mode throttle(::vehicle_interface::msg::VehicleCommand::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_VehicleCommand_mode(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleCommand msg_;
};

class Init_VehicleCommand_steering
{
public:
  Init_VehicleCommand_steering()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleCommand_throttle steering(::vehicle_interface::msg::VehicleCommand::_steering_type arg)
  {
    msg_.steering = std::move(arg);
    return Init_VehicleCommand_throttle(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interface::msg::VehicleCommand>()
{
  return vehicle_interface::msg::builder::Init_VehicleCommand_steering();
}

}  // namespace vehicle_interface

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_
