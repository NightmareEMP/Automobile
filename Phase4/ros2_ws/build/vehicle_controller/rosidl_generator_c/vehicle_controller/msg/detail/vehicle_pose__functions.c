// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice
#include "vehicle_controller/msg/detail/vehicle_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vehicle_controller__msg__VehiclePose__init(vehicle_controller__msg__VehiclePose * msg)
{
  if (!msg) {
    return false;
  }
  // steering
  // throttle
  // mode
  return true;
}

void
vehicle_controller__msg__VehiclePose__fini(vehicle_controller__msg__VehiclePose * msg)
{
  if (!msg) {
    return;
  }
  // steering
  // throttle
  // mode
}

bool
vehicle_controller__msg__VehiclePose__are_equal(const vehicle_controller__msg__VehiclePose * lhs, const vehicle_controller__msg__VehiclePose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // steering
  if (lhs->steering != rhs->steering) {
    return false;
  }
  // throttle
  if (lhs->throttle != rhs->throttle) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  return true;
}

bool
vehicle_controller__msg__VehiclePose__copy(
  const vehicle_controller__msg__VehiclePose * input,
  vehicle_controller__msg__VehiclePose * output)
{
  if (!input || !output) {
    return false;
  }
  // steering
  output->steering = input->steering;
  // throttle
  output->throttle = input->throttle;
  // mode
  output->mode = input->mode;
  return true;
}

vehicle_controller__msg__VehiclePose *
vehicle_controller__msg__VehiclePose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_controller__msg__VehiclePose * msg = (vehicle_controller__msg__VehiclePose *)allocator.allocate(sizeof(vehicle_controller__msg__VehiclePose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_controller__msg__VehiclePose));
  bool success = vehicle_controller__msg__VehiclePose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_controller__msg__VehiclePose__destroy(vehicle_controller__msg__VehiclePose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_controller__msg__VehiclePose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_controller__msg__VehiclePose__Sequence__init(vehicle_controller__msg__VehiclePose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_controller__msg__VehiclePose * data = NULL;

  if (size) {
    data = (vehicle_controller__msg__VehiclePose *)allocator.zero_allocate(size, sizeof(vehicle_controller__msg__VehiclePose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_controller__msg__VehiclePose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_controller__msg__VehiclePose__fini(&data[i - 1]);
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
vehicle_controller__msg__VehiclePose__Sequence__fini(vehicle_controller__msg__VehiclePose__Sequence * array)
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
      vehicle_controller__msg__VehiclePose__fini(&array->data[i]);
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

vehicle_controller__msg__VehiclePose__Sequence *
vehicle_controller__msg__VehiclePose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_controller__msg__VehiclePose__Sequence * array = (vehicle_controller__msg__VehiclePose__Sequence *)allocator.allocate(sizeof(vehicle_controller__msg__VehiclePose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_controller__msg__VehiclePose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_controller__msg__VehiclePose__Sequence__destroy(vehicle_controller__msg__VehiclePose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_controller__msg__VehiclePose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_controller__msg__VehiclePose__Sequence__are_equal(const vehicle_controller__msg__VehiclePose__Sequence * lhs, const vehicle_controller__msg__VehiclePose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_controller__msg__VehiclePose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_controller__msg__VehiclePose__Sequence__copy(
  const vehicle_controller__msg__VehiclePose__Sequence * input,
  vehicle_controller__msg__VehiclePose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vehicle_controller__msg__VehiclePose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_controller__msg__VehiclePose * data =
      (vehicle_controller__msg__VehiclePose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_controller__msg__VehiclePose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_controller__msg__VehiclePose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_controller__msg__VehiclePose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
