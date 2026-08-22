// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__TRAITS_HPP_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_interface/msg/detail/vehicle_feedback__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleFeedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: telemetry_seq
  {
    out << "telemetry_seq: ";
    rosidl_generator_traits::value_to_yaml(msg.telemetry_seq, out);
    out << ", ";
  }

  // member: last_cmd_seq
  {
    out << "last_cmd_seq: ";
    rosidl_generator_traits::value_to_yaml(msg.last_cmd_seq, out);
    out << ", ";
  }

  // member: stm32_timestamp_ms
  {
    out << "stm32_timestamp_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.stm32_timestamp_ms, out);
    out << ", ";
  }

  // member: erpm
  {
    out << "erpm: ";
    rosidl_generator_traits::value_to_yaml(msg.erpm, out);
    out << ", ";
  }

  // member: motor_current_x10
  {
    out << "motor_current_x10: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_current_x10, out);
    out << ", ";
  }

  // member: duty_x1000
  {
    out << "duty_x1000: ";
    rosidl_generator_traits::value_to_yaml(msg.duty_x1000, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleFeedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: telemetry_seq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "telemetry_seq: ";
    rosidl_generator_traits::value_to_yaml(msg.telemetry_seq, out);
    out << "\n";
  }

  // member: last_cmd_seq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_cmd_seq: ";
    rosidl_generator_traits::value_to_yaml(msg.last_cmd_seq, out);
    out << "\n";
  }

  // member: stm32_timestamp_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stm32_timestamp_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.stm32_timestamp_ms, out);
    out << "\n";
  }

  // member: erpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "erpm: ";
    rosidl_generator_traits::value_to_yaml(msg.erpm, out);
    out << "\n";
  }

  // member: motor_current_x10
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_current_x10: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_current_x10, out);
    out << "\n";
  }

  // member: duty_x1000
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "duty_x1000: ";
    rosidl_generator_traits::value_to_yaml(msg.duty_x1000, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleFeedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vehicle_interface

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_interface::msg::VehicleFeedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_interface::msg::VehicleFeedback & msg)
{
  return vehicle_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_interface::msg::VehicleFeedback>()
{
  return "vehicle_interface::msg::VehicleFeedback";
}

template<>
inline const char * name<vehicle_interface::msg::VehicleFeedback>()
{
  return "vehicle_interface/msg/VehicleFeedback";
}

template<>
struct has_fixed_size<vehicle_interface::msg::VehicleFeedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_interface::msg::VehicleFeedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_interface::msg::VehicleFeedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__TRAITS_HPP_
