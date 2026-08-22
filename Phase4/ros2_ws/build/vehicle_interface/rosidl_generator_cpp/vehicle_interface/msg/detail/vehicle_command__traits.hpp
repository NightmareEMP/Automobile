// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_interface:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_interface/msg/detail/vehicle_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: steering
  {
    out << "steering: ";
    rosidl_generator_traits::value_to_yaml(msg.steering, out);
    out << ", ";
  }

  // member: throttle
  {
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: steering
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering: ";
    rosidl_generator_traits::value_to_yaml(msg.steering, out);
    out << "\n";
  }

  // member: throttle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << "\n";
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleCommand & msg, bool use_flow_style = false)
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
  const vehicle_interface::msg::VehicleCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_interface::msg::VehicleCommand & msg)
{
  return vehicle_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_interface::msg::VehicleCommand>()
{
  return "vehicle_interface::msg::VehicleCommand";
}

template<>
inline const char * name<vehicle_interface::msg::VehicleCommand>()
{
  return "vehicle_interface/msg/VehicleCommand";
}

template<>
struct has_fixed_size<vehicle_interface::msg::VehicleCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_interface::msg::VehicleCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_interface::msg::VehicleCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_
