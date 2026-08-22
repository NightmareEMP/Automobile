// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_controller:msg/VehiclePose.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_HPP_
#define VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_controller__msg__VehiclePose __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_controller__msg__VehiclePose __declspec(deprecated)
#endif

namespace vehicle_controller
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehiclePose_
{
  using Type = VehiclePose_<ContainerAllocator>;

  explicit VehiclePose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering = 0;
      this->throttle = 0;
      this->mode = 0;
    }
  }

  explicit VehiclePose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering = 0;
      this->throttle = 0;
      this->mode = 0;
    }
  }

  // field types and members
  using _steering_type =
    int16_t;
  _steering_type steering;
  using _throttle_type =
    int16_t;
  _throttle_type throttle;
  using _mode_type =
    uint8_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__steering(
    const int16_t & _arg)
  {
    this->steering = _arg;
    return *this;
  }
  Type & set__throttle(
    const int16_t & _arg)
  {
    this->throttle = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_controller::msg::VehiclePose_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_controller::msg::VehiclePose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_controller::msg::VehiclePose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_controller::msg::VehiclePose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_controller__msg__VehiclePose
    std::shared_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_controller__msg__VehiclePose
    std::shared_ptr<vehicle_controller::msg::VehiclePose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehiclePose_ & other) const
  {
    if (this->steering != other.steering) {
      return false;
    }
    if (this->throttle != other.throttle) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehiclePose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehiclePose_

// alias to use template instance with default allocator
using VehiclePose =
  vehicle_controller::msg::VehiclePose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_controller

#endif  // VEHICLE_CONTROLLER__MSG__DETAIL__VEHICLE_POSE__STRUCT_HPP_
