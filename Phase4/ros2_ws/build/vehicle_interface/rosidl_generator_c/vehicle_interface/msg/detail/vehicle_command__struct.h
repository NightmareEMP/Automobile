// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interface:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_H_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehicleCommand in the package vehicle_interface.
/**
  * VehicleCommand.msg
 */
typedef struct vehicle_interface__msg__VehicleCommand
{
  int16_t steering;
  int16_t throttle;
  uint8_t mode;
} vehicle_interface__msg__VehicleCommand;

// Struct for a sequence of vehicle_interface__msg__VehicleCommand.
typedef struct vehicle_interface__msg__VehicleCommand__Sequence
{
  vehicle_interface__msg__VehicleCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interface__msg__VehicleCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_H_
