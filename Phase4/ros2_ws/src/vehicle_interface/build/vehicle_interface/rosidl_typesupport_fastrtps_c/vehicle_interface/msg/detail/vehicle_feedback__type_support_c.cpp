// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice
#include "vehicle_interface/msg/detail/vehicle_feedback__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vehicle_interface/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__struct.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _VehicleFeedback__ros_msg_type = vehicle_interface__msg__VehicleFeedback;

static bool _VehicleFeedback__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _VehicleFeedback__ros_msg_type * ros_message = static_cast<const _VehicleFeedback__ros_msg_type *>(untyped_ros_message);
  // Field name: telemetry_seq
  {
    cdr << ros_message->telemetry_seq;
  }

  // Field name: last_cmd_seq
  {
    cdr << ros_message->last_cmd_seq;
  }

  // Field name: stm32_timestamp_ms
  {
    cdr << ros_message->stm32_timestamp_ms;
  }

  // Field name: erpm
  {
    cdr << ros_message->erpm;
  }

  // Field name: motor_current_x10
  {
    cdr << ros_message->motor_current_x10;
  }

  // Field name: duty_x1000
  {
    cdr << ros_message->duty_x1000;
  }

  return true;
}

static bool _VehicleFeedback__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _VehicleFeedback__ros_msg_type * ros_message = static_cast<_VehicleFeedback__ros_msg_type *>(untyped_ros_message);
  // Field name: telemetry_seq
  {
    cdr >> ros_message->telemetry_seq;
  }

  // Field name: last_cmd_seq
  {
    cdr >> ros_message->last_cmd_seq;
  }

  // Field name: stm32_timestamp_ms
  {
    cdr >> ros_message->stm32_timestamp_ms;
  }

  // Field name: erpm
  {
    cdr >> ros_message->erpm;
  }

  // Field name: motor_current_x10
  {
    cdr >> ros_message->motor_current_x10;
  }

  // Field name: duty_x1000
  {
    cdr >> ros_message->duty_x1000;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interface
size_t get_serialized_size_vehicle_interface__msg__VehicleFeedback(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _VehicleFeedback__ros_msg_type * ros_message = static_cast<const _VehicleFeedback__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name telemetry_seq
  {
    size_t item_size = sizeof(ros_message->telemetry_seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name last_cmd_seq
  {
    size_t item_size = sizeof(ros_message->last_cmd_seq);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name stm32_timestamp_ms
  {
    size_t item_size = sizeof(ros_message->stm32_timestamp_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name erpm
  {
    size_t item_size = sizeof(ros_message->erpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name motor_current_x10
  {
    size_t item_size = sizeof(ros_message->motor_current_x10);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name duty_x1000
  {
    size_t item_size = sizeof(ros_message->duty_x1000);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _VehicleFeedback__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vehicle_interface__msg__VehicleFeedback(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vehicle_interface
size_t max_serialized_size_vehicle_interface__msg__VehicleFeedback(
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

  // member: telemetry_seq
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: last_cmd_seq
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: stm32_timestamp_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: erpm
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: motor_current_x10
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: duty_x1000
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
    using DataType = vehicle_interface__msg__VehicleFeedback;
    is_plain =
      (
      offsetof(DataType, duty_x1000) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _VehicleFeedback__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vehicle_interface__msg__VehicleFeedback(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_VehicleFeedback = {
  "vehicle_interface::msg",
  "VehicleFeedback",
  _VehicleFeedback__cdr_serialize,
  _VehicleFeedback__cdr_deserialize,
  _VehicleFeedback__get_serialized_size,
  _VehicleFeedback__max_serialized_size
};

static rosidl_message_type_support_t _VehicleFeedback__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_VehicleFeedback,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vehicle_interface, msg, VehicleFeedback)() {
  return &_VehicleFeedback__type_support;
}

#if defined(__cplusplus)
}
#endif
