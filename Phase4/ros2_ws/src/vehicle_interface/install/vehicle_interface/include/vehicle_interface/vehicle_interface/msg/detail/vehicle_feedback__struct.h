// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_H_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehicleFeedback in the package vehicle_interface.
/**
  * VehicleFeedback.msg
 */
typedef struct vehicle_interface__msg__VehicleFeedback
{
  uint16_t telemetry_seq;
  uint16_t last_cmd_seq;
  uint32_t stm32_timestamp_ms;
  int32_t erpm;
  int16_t motor_current_x10;
  int16_t duty_x1000;
} vehicle_interface__msg__VehicleFeedback;

// Struct for a sequence of vehicle_interface__msg__VehicleFeedback.
typedef struct vehicle_interface__msg__VehicleFeedback__Sequence
{
  vehicle_interface__msg__VehicleFeedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_interface__msg__VehicleFeedback__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_H_
