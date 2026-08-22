// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__BUILDER_HPP_
#define VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_controller/msg/detail/vehicle_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_controller
{

namespace msg
{

namespace builder
{

class Init_VehiclePose_mode
{
public:
  explicit Init_VehiclePose_mode(::vehicle_controller::msg::VehiclePose & msg)
  : msg_(msg)
  {}
  ::vehicle_controller::msg::VehiclePose mode(::vehicle_controller::msg::VehiclePose::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_controller::msg::VehiclePose msg_;
};

class Init_VehiclePose_throttle
{
public:
  explicit Init_VehiclePose_throttle(::vehicle_controller::msg::VehiclePose & msg)
  : msg_(msg)
  {}
  Init_VehiclePose_mode throttle(::vehicle_controller::msg::VehiclePose::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_VehiclePose_mode(msg_);
  }

private:
  ::vehicle_controller::msg::VehiclePose msg_;
};

class Init_VehiclePose_steering
{
public:
  Init_VehiclePose_steering()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehiclePose_throttle steering(::vehicle_controller::msg::VehiclePose::_steering_type arg)
  {
    msg_.steering = std::move(arg);
    return Init_VehiclePose_throttle(msg_);
  }

private:
  ::vehicle_controller::msg::VehiclePose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_controller::msg::VehiclePose>()
{
  return vehicle_controller::msg::builder::Init_VehiclePose_steering();
}

}  // namespace vehicle_controller

#endif  // VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__BUILDER_HPP_
