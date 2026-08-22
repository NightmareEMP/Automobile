// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_H_
#define VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehiclePose in the package vehicle_controller.
/**
  * VehicleCommand.msg
 */
typedef struct vehicle_controller__msg__VehiclePose
{
  int16_t steering;
  int16_t throttle;
  uint8_t mode;
} vehicle_controller__msg__VehiclePose;

// Struct for a sequence of vehicle_controller__msg__VehiclePose.
typedef struct vehicle_controller__msg__VehiclePose__Sequence
{
  vehicle_controller__msg__VehiclePose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_controller__msg__VehiclePose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_H_
