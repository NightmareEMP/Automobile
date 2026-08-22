// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice
#include "vehicle_interface/msg/detail/vehicle_feedback__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vehicle_interface/msg/detail/vehicle_feedback__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace vehicle_interface
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interface
cdr_serialize(
  const vehicle_interface::msg::VehicleFeedback & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: telemetry_seq
  cdr << ros_message.telemetry_seq;
  // Member: last_cmd_seq
  cdr << ros_message.last_cmd_seq;
  // Member: stm32_timestamp_ms
  cdr << ros_message.stm32_timestamp_ms;
  // Member: erpm
  cdr << ros_message.erpm;
  // Member: motor_current_x10
  cdr << ros_message.motor_current_x10;
  // Member: duty_x1000
  cdr << ros_message.duty_x1000;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interface
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vehicle_interface::msg::VehicleFeedback & ros_message)
{
  // Member: telemetry_seq
  cdr >> ros_message.telemetry_seq;

  // Member: last_cmd_seq
  cdr >> ros_message.last_cmd_seq;

  // Member: stm32_timestamp_ms
  cdr >> ros_message.stm32_timestamp_ms;

  // Member: erpm
  cdr >> ros_message.erpm;

  // Member: motor_current_x10
  cdr >> ros_message.motor_current_x10;

  // Member: duty_x1000
  cdr >> ros_message.duty_x1000;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interface
get_serialized_size(
  const vehicle_interface::msg::VehicleFeedback & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: telemetry_seq
  {
    size_t item_size = sizeof(ros_message.telemetry_seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: last_cmd_seq
  {
    size_t item_size = sizeof(ros_message.last_cmd_seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: stm32_timestamp_ms
  {
    size_t item_size = sizeof(ros_message.stm32_timestamp_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: erpm
  {
    size_t item_size = sizeof(ros_message.erpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor_current_x10
  {
    size_t item_size = sizeof(ros_message.motor_current_x10);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: duty_x1000
  {
    size_t item_size = sizeof(ros_message.duty_x1000);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vehicle_interface
max_serialized_size_VehicleFeedback(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: telemetry_seq
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: last_cmd_seq
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: stm32_timestamp_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: erpm
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: motor_current_x10
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: duty_x1000
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vehicle_interface::msg::VehicleFeedback;
    is_plain =
      (
      offsetof(DataType, duty_x1000) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _VehicleFeedback__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vehicle_interface::msg::VehicleFeedback *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _VehicleFeedback__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vehicle_interface::msg::VehicleFeedback *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _VehicleFeedback__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vehicle_interface::msg::VehicleFeedback *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _VehicleFeedback__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_VehicleFeedback(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _VehicleFeedback__callbacks = {
  "vehicle_interface::msg",
  "VehicleFeedback",
  _VehicleFeedback__cdr_serialize,
  _VehicleFeedback__cdr_deserialize,
  _VehicleFeedback__get_serialized_size,
  _VehicleFeedback__max_serialized_size
};

static rosidl_message_type_support_t _VehicleFeedback__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_VehicleFeedback__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vehicle_interface

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vehicle_interface
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_interface::msg::VehicleFeedback>()
{
  return &vehicle_interface::msg::typesupport_fastrtps_cpp::_VehicleFeedback__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vehicle_interface, msg, VehicleFeedback)() {
  return &vehicle_interface::msg::typesupport_fastrtps_cpp::_VehicleFeedback__handle;
}

#ifdef __cplusplus
}
#endif
