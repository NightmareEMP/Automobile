// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_controller/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "vehicle_controller/msg/detail/vehicle_pose__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace vehicle_controller
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_controller
cdr_serialize(
  const vehicle_controller::msg::VehiclePose & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_controller
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_controller::msg::VehiclePose & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_controller
get_serialized_size(
  const vehicle_controller::msg::VehiclePose & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_controller
max_serialized_size_VehiclePose(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vehicle_controller

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_controller
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_controller, msg, VehiclePose)();

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
