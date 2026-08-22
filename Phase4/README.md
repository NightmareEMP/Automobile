# Learning order:
- Node                    (V)
- Publisher / Subscriber  (V)
- Topic                   (V)
- Message types           (V)
- Timer / callback        (V)
- Parameters              (V)
- TF2
- Launch files
1. Simple test on publisher and subscriber 



# Send CMD:
```
another ROS2 node
       |
       | publishes VehicleCommand
       v
/vehicle_command
       |
       v
command_sub_
       |
       v
command_callback()
       |
       +--> SetSteering()
       +--> SetThrottle()
       +--> SetMode()
       |
       v
atomic desired values
       |
       v
TxLoop()
       |
       v
UART → STM32
```
# Receive Feedback
```
STM32
 ↓
UART
 ↓
Feedback struct
 ↓
convert to ROS VehicleFeedback
 ↓
feedback_pub_->publish()
 ↓
/vehicle_feedback
```

# Overview
```
                        ROS2

/vehicle_command                     /vehicle_feedback
       |                                    ^
       v                                    |
 command_sub_                         feedback_pub_
       |                                    ^
       v                                    |
command_callback()                       RxLoop()
       |                                    ^
       v                                    |
 desired_*                              Feedback
       |                                    ^
       v                                    |
    TxLoop()                              UART
       |                                    ^
       +------------ UART ------------------+
                     |
                    STM32
```


# Useful cmd
source /opt/ros/humble/setup.bash
source install/setup.bash
colcon build --packages-up-to {PACKAGE_TARGET}
ros2 run {PACKAGE_TARGET} {CMAKE_TARGET}
 
// Send msg from terminal
ros2 topic pub /vehicle_pose vehicle_controller/msg/VehiclePose "{steering: 1520, throttle: 0, mode: 1}" -r 10

ros2 topic pub /vehicle_pose vehicle_controller/msg/VehiclePose "{steering: 1520, throttle: 1000, mode: 1}" -r 10

ros2 topic pub /vehicle_pose vehicle_controller/msg/VehiclePose "{steering: 1520, throttle: 3000, mode: 1}" -r 10

ros2 topic pub /vehicle_pose vehicle_controller/msg/VehiclePose "{steering: 1650, throttle: 2500, mode: 1}" -r 10