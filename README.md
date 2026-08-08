# Autonomous Vehicle Platform

## 1. Project Overview

This project develops an autonomous vehicle platform using an NVIDIA Jetson as the high-level computing unit and an STM32 microcontroller as the low-level control unit.

The Jetson is responsible for computationally intensive tasks such as sensor processing, localization, mapping, path planning, and autonomous navigation, while the STM32 handles real-time vehicle control, including steering, motor control, and communication with vehicle hardware.

The platform primarily uses LiDAR and IMU data for environmental perception and vehicle motion estimation. The system is designed as a modular development platform so that different localization, mapping, and path-planning algorithms can be evaluated and integrated as the project progresses.

## 2. Goals
- Develope fully autonomus vehicle with manual interrupt
- Build reliable steering and motor control system
- Separate high-level computation from real-time actuator control
- Develope Map-Based Autonomous Navigation
- Develope Mapless Autonomous Navigation

## 3. Current Status

| Phase | Description | Status |
|---|---|---|
| Phase 1 | Steering servo control | Completed |
| Phase 2 | Motor control | Completed |
| Phase 3 | Integrated vehicle control | Compete |
| Phase 4 | Simple ROS testing | In Progress |

## 4. Hardware Components

Brief component list here.

- For wiring details, see [Hardware Architecture](./docs/Hardware/HardwareArchitecture/README.md).

- For Flisky 6.7v Pro settings see [VESC Settings](./docs/Hardware/VESC_setting/README.md).

## 5. Software Architecture

Brief software overview here.

For more detail, see [Software Architecture](./docs/software-architecture.md).

## 6. Control and Compute Unit Separation

Explain why Jetson and STM32 have different responsibilities.

## 7. Communication Flow

Briefly describe UART, CAN, SBUS, or other interfaces.

For packet definitions, see
[Communication Protocol](./docs/communication-protocol.md).

## 8. Development Phases

### [Phase 1 — Steering Servo Control](./Phase1/README.md)

STM32 PWM control, steering calibration, startup behavior, and safety limits.

### [Phase 2 — Motor Control](./Phase2/README.md)

Motor commands, motor-controller communication, and feedback handling.

### [Phase 3 — Integrated Vehicle Control](./Phase3/README.md)

Combined steering and throttle control, feedback, modes, timeouts, and failsafe behavior.

### Future Phases

Planned work includes Jetson integration, localization, planning, and autonomous driving.

## 9. Repository Structure

```text
autonomous-vehicle/
├── README.md
├── docs/
├── phase1-servo-control/
├── phase2-motor-control/
└── phase3-integrated-control/
```
## 10. Resources

# Next Step
1. Check if vehicle drive straight
2. Implement INA226 device driver
3. Add ROS2 Development
