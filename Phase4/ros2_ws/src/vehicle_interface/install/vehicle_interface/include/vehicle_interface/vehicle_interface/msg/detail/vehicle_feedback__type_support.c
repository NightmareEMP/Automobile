// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_interface/msg/detail/vehicle_feedback__rosidl_typesupport_introspection_c.h"
#include "vehicle_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__functions.h"
#include "vehicle_interface/msg/detail/vehicle_feedback__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_interface__msg__VehicleFeedback__init(message_memory);
}

void vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_fini_function(void * message_memory)
{
  vehicle_interface__msg__VehicleFeedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_member_array[6] = {
  {
    "telemetry_seq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, telemetry_seq),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "last_cmd_seq",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, last_cmd_seq),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stm32_timestamp_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, stm32_timestamp_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "erpm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, erpm),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor_current_x10",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, motor_current_x10),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "duty_x1000",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_interface__msg__VehicleFeedback, duty_x1000),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_members = {
  "vehicle_interface__msg",  // message namespace
  "VehicleFeedback",  // message name
  6,  // number of fields
  sizeof(vehicle_interface__msg__VehicleFeedback),
  vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_member_array,  // message members
  vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_type_support_handle = {
  0,
  &vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_interface, msg, VehicleFeedback)() {
  if (!vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_type_support_handle.typesupport_identifier) {
    vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_interface__msg__VehicleFeedback__rosidl_typesupport_introspection_c__VehicleFeedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
