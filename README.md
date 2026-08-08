# Autonomous Vehicle Platform
###### tags: `SideProject`
## 1. Project Overview

This project develops an autonomous vehicle platform using a Jetson as the
high-level compute unit and an STM32 as the low-level control unit.

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
| Phase 3 | Integrated vehicle control | In progress |

## 4. System Architecture

Brief overview here.

For more detail, see [System Architecture](./docs/system-architecture.md).

## 5. Hardware Components

Brief component list here.

For wiring details, see [Wiring and Power](./docs/wiring-and-power.md).

## 6. Control and Compute Unit Separation

Explain why Jetson and STM32 have different responsibilities.

## 7. Software Architecture

Brief software overview here.

For more detail, see [Software Architecture](./docs/software-architecture.md).

## 8. Communication Flow

Briefly describe UART, CAN, SBUS, or other interfaces.

For packet definitions, see
[Communication Protocol](./docs/communication-protocol.md).

## 9. Development Phases

### [Phase 1 — Steering Servo Control](./phase1-servo-control/)

STM32 PWM control, steering calibration, startup behavior, and safety limits.

### [Phase 2 — Motor Control](./phase2-motor-control/)

Motor commands, motor-controller communication, and feedback handling.

### [Phase 3 — Integrated Vehicle Control](./phase3-integrated-control/)

Combined steering and throttle control, feedback, modes, timeouts, and failsafe behavior.

### Future Phases

Planned work includes Jetson integration, localization, planning, and autonomous driving.

## 10. Repository Structure

```text
autonomous-vehicle/
├── README.md
├── docs/
├── phase1-servo-control/
├── phase2-motor-control/
└── phase3-integrated-control/
```
## 11. Resources

# Next Step
1. Check if vehicle drive straight
2. Implement INA226 device driver
3. Add ROS2 Development
