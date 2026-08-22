// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_interface:msg/VehicleFeedback.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_HPP_
#define VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_interface__msg__VehicleFeedback __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_interface__msg__VehicleFeedback __declspec(deprecated)
#endif

namespace vehicle_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleFeedback_
{
  using Type = VehicleFeedback_<ContainerAllocator>;

  explicit VehicleFeedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->telemetry_seq = 0;
      this->last_cmd_seq = 0;
      this->stm32_timestamp_ms = 0ul;
      this->erpm = 0l;
      this->motor_current_x10 = 0;
      this->duty_x1000 = 0;
    }
  }

  explicit VehicleFeedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->telemetry_seq = 0;
      this->last_cmd_seq = 0;
      this->stm32_timestamp_ms = 0ul;
      this->erpm = 0l;
      this->motor_current_x10 = 0;
      this->duty_x1000 = 0;
    }
  }

  // field types and members
  using _telemetry_seq_type =
    uint16_t;
  _telemetry_seq_type telemetry_seq;
  using _last_cmd_seq_type =
    uint16_t;
  _last_cmd_seq_type last_cmd_seq;
  using _stm32_timestamp_ms_type =
    uint32_t;
  _stm32_timestamp_ms_type stm32_timestamp_ms;
  using _erpm_type =
    int32_t;
  _erpm_type erpm;
  using _motor_current_x10_type =
    int16_t;
  _motor_current_x10_type motor_current_x10;
  using _duty_x1000_type =
    int16_t;
  _duty_x1000_type duty_x1000;

  // setters for named parameter idiom
  Type & set__telemetry_seq(
    const uint16_t & _arg)
  {
    this->telemetry_seq = _arg;
    return *this;
  }
  Type & set__last_cmd_seq(
    const uint16_t & _arg)
  {
    this->last_cmd_seq = _arg;
    return *this;
  }
  Type & set__stm32_timestamp_ms(
    const uint32_t & _arg)
  {
    this->stm32_timestamp_ms = _arg;
    return *this;
  }
  Type & set__erpm(
    const int32_t & _arg)
  {
    this->erpm = _arg;
    return *this;
  }
  Type & set__motor_current_x10(
    const int16_t & _arg)
  {
    this->motor_current_x10 = _arg;
    return *this;
  }
  Type & set__duty_x1000(
    const int16_t & _arg)
  {
    this->duty_x1000 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_interface__msg__VehicleFeedback
    std::shared_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_interface__msg__VehicleFeedback
    std::shared_ptr<vehicle_interface::msg::VehicleFeedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleFeedback_ & other) const
  {
    if (this->telemetry_seq != other.telemetry_seq) {
      return false;
    }
    if (this->last_cmd_seq != other.last_cmd_seq) {
      return false;
    }
    if (this->stm32_timestamp_ms != other.stm32_timestamp_ms) {
      return false;
    }
    if (this->erpm != other.erpm) {
      return false;
    }
    if (this->motor_current_x10 != other.motor_current_x10) {
      return false;
    }
    if (this->duty_x1000 != other.duty_x1000) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleFeedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleFeedback_

// alias to use template instance with default allocator
using VehicleFeedback =
  vehicle_interface::msg::VehicleFeedback_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_interface

#endif  // VEHICLE_INTERFACE__MSG__DETAIL__VEHICLE_FEEDBACK__STRUCT_HPP_
