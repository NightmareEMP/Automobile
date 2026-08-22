// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice
#include "vehicle_interface/msg/detail/vehicle_feedback__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vehicle_interface__msg__VehicleFeedback__init(vehicle_interface__msg__VehicleFeedback * msg)
{
  if (!msg) {
    return false;
  }
  // telemetry_seq
  // last_cmd_seq
  // stm32_timestamp_ms
  // erpm
  // motor_current_x10
  // duty_x1000
  return true;
}

void
vehicle_interface__msg__VehicleFeedback__fini(vehicle_interface__msg__VehicleFeedback * msg)
{
  if (!msg) {
    return;
  }
  // telemetry_seq
  // last_cmd_seq
  // stm32_timestamp_ms
  // erpm
  // motor_current_x10
  // duty_x1000
}

bool
vehicle_interface__msg__VehicleFeedback__are_equal(const vehicle_interface__msg__VehicleFeedback * lhs, const vehicle_interface__msg__VehicleFeedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // telemetry_seq
  if (lhs->telemetry_seq != rhs->telemetry_seq) {
    return false;
  }
  // last_cmd_seq
  if (lhs->last_cmd_seq != rhs->last_cmd_seq) {
    return false;
  }
  // stm32_timestamp_ms
  if (lhs->stm32_timestamp_ms != rhs->stm32_timestamp_ms) {
    return false;
  }
  // erpm
  if (lhs->erpm != rhs->erpm) {
    return false;
  }
  // motor_current_x10
  if (lhs->motor_current_x10 != rhs->motor_current_x10) {
    return false;
  }
  // duty_x1000
  if (lhs->duty_x1000 != rhs->duty_x1000) {
    return false;
  }
  return true;
}

bool
vehicle_interface__msg__VehicleFeedback__copy(
  const vehicle_interface__msg__VehicleFeedback * input,
  vehicle_interface__msg__VehicleFeedback * output)
{
  if (!input || !output) {
    return false;
  }
  // telemetry_seq
  output->telemetry_seq = input->telemetry_seq;
  // last_cmd_seq
  output->last_cmd_seq = input->last_cmd_seq;
  // stm32_timestamp_ms
  output->stm32_timestamp_ms = input->stm32_timestamp_ms;
  // erpm
  output->erpm = input->erpm;
  // motor_current_x10
  output->motor_current_x10 = input->motor_current_x10;
  // duty_x1000
  output->duty_x1000 = input->duty_x1000;
  return true;
}

vehicle_interface__msg__VehicleFeedback *
vehicle_interface__msg__VehicleFeedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interface__msg__VehicleFeedback * msg = (vehicle_interface__msg__VehicleFeedback *)allocator.allocate(sizeof(vehicle_interface__msg__VehicleFeedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_interface__msg__VehicleFeedback));
  bool success = vehicle_interface__msg__VehicleFeedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_interface__msg__VehicleFeedback__destroy(vehicle_interface__msg__VehicleFeedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_interface__msg__VehicleFeedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_interface__msg__VehicleFeedback__Sequence__init(vehicle_interface__msg__VehicleFeedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interface__msg__VehicleFeedback * data = NULL;

  if (size) {
    data = (vehicle_interface__msg__VehicleFeedback *)allocator.zero_allocate(size, sizeof(vehicle_interface__msg__VehicleFeedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_interface__msg__VehicleFeedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_interface__msg__VehicleFeedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vehicle_interface__msg__VehicleFeedback__Sequence__fini(vehicle_interface__msg__VehicleFeedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vehicle_interface__msg__VehicleFeedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vehicle_interface__msg__VehicleFeedback__Sequence *
vehicle_interface__msg__VehicleFeedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_interface__msg__VehicleFeedback__Sequence * array = (vehicle_interface__msg__VehicleFeedback__Sequence *)allocator.allocate(sizeof(vehicle_interface__msg__VehicleFeedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_interface__msg__VehicleFeedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_interface__msg__VehicleFeedback__Sequence__destroy(vehicle_interface__msg__VehicleFeedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_interface__msg__VehicleFeedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_interface__msg__VehicleFeedback__Sequence__are_equal(const vehicle_interface__msg__VehicleFeedback__Sequence * lhs, const vehicle_interface__msg__VehicleFeedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_interface__msg__VehicleFeedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_interface__msg__VehicleFeedback__Sequence__copy(
  const vehicle_interface__msg__VehicleFeedback__Sequence * input,
  vehicle_interface__msg__VehicleFeedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_interface__msg__VehicleFeedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_interface__msg__VehicleFeedback * data =
      (vehicle_interface__msg__VehicleFeedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_interface__msg__VehicleFeedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_interface__msg__VehicleFeedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_interface__msg__VehicleFeedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
