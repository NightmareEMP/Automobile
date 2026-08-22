// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__BUILDER_HPP_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_interface/msg/detail/vehicle_feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_interface
{

namespace msg
{

namespace builder
{

class Init_VehicleFeedback_duty_x1000
{
public:
  explicit Init_VehicleFeedback_duty_x1000(::vehicle_interface::msg::VehicleFeedback & msg)
  : msg_(msg)
  {}
  ::vehicle_interface::msg::VehicleFeedback duty_x1000(::vehicle_interface::msg::VehicleFeedback::_duty_x1000_type arg)
  {
    msg_.duty_x1000 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

class Init_VehicleFeedback_motor_current_x10
{
public:
  explicit Init_VehicleFeedback_motor_current_x10(::vehicle_interface::msg::VehicleFeedback & msg)
  : msg_(msg)
  {}
  Init_VehicleFeedback_duty_x1000 motor_current_x10(::vehicle_interface::msg::VehicleFeedback::_motor_current_x10_type arg)
  {
    msg_.motor_current_x10 = std::move(arg);
    return Init_VehicleFeedback_duty_x1000(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

class Init_VehicleFeedback_erpm
{
public:
  explicit Init_VehicleFeedback_erpm(::vehicle_interface::msg::VehicleFeedback & msg)
  : msg_(msg)
  {}
  Init_VehicleFeedback_motor_current_x10 erpm(::vehicle_interface::msg::VehicleFeedback::_erpm_type arg)
  {
    msg_.erpm = std::move(arg);
    return Init_VehicleFeedback_motor_current_x10(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

class Init_VehicleFeedback_stm32_timestamp_ms
{
public:
  explicit Init_VehicleFeedback_stm32_timestamp_ms(::vehicle_interface::msg::VehicleFeedback & msg)
  : msg_(msg)
  {}
  Init_VehicleFeedback_erpm stm32_timestamp_ms(::vehicle_interface::msg::VehicleFeedback::_stm32_timestamp_ms_type arg)
  {
    msg_.stm32_timestamp_ms = std::move(arg);
    return Init_VehicleFeedback_erpm(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

class Init_VehicleFeedback_last_cmd_seq
{
public:
  explicit Init_VehicleFeedback_last_cmd_seq(::vehicle_interface::msg::VehicleFeedback & msg)
  : msg_(msg)
  {}
  Init_VehicleFeedback_stm32_timestamp_ms last_cmd_seq(::vehicle_interface::msg::VehicleFeedback::_last_cmd_seq_type arg)
  {
    msg_.last_cmd_seq = std::move(arg);
    return Init_VehicleFeedback_stm32_timestamp_ms(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

class Init_VehicleFeedback_telemetry_seq
{
public:
  Init_VehicleFeedback_telemetry_seq()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleFeedback_last_cmd_seq telemetry_seq(::vehicle_interface::msg::VehicleFeedback::_telemetry_seq_type arg)
  {
    msg_.telemetry_seq = std::move(arg);
    return Init_VehicleFeedback_last_cmd_seq(msg_);
  }

private:
  ::vehicle_interface::msg::VehicleFeedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_interface::msg::VehicleFeedback>()
{
  return vehicle_interface::msg::builder::Init_VehicleFeedback_telemetry_seq();
}

}  // namespace vehicle_interface

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__BUILDER_HPP_
