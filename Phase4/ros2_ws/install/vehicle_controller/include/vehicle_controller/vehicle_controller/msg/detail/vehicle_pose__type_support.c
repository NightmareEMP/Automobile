// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_controller/msg/detail/vehicle_pose__rosidl_typesupport_introspection_c.h"
#include "vehicle_controller/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_controller/msg/detail/vehicle_pose__functions.h"
#include "vehicle_controller/msg/detail/vehicle_pose__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_controller__msg__VehiclePose__init(message_memory);
}

void vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_fini_function(void * message_memory)
{
  vehicle_controller__msg__VehiclePose__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_member_array[3] = {
  {
    "steering",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_controller__msg__VehiclePose, steering),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "throttle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_controller__msg__VehiclePose, throttle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_controller__msg__VehiclePose, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_members = {
  "vehicle_controller__msg",  // message namespace
  "VehiclePose",  // message name
  3,  // number of fields
  sizeof(vehicle_controller__msg__VehiclePose),
  vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_member_array,  // message members
  vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_type_support_handle = {
  0,
  &vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_controller
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_controller, msg, VehiclePose)() {
  if (!vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_type_support_handle.typesupport_identifier) {
    vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_controller__msg__VehiclePose__rosidl_typesupport_introspection_c__VehiclePose_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
