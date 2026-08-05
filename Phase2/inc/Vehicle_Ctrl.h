#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>



typedef struct  {
    uint8_t  header1;      // 0xAB
    uint8_t  header2;      // 0x55
    int16_t  steering;     // 1320 ~ 1720
    int16_t  throttle;     // TODO
    uint8_t  mode;         // 0=manual, 1=auto, 2=estop
    uint8_t  seq;          // packet counter
    uint16_t crc;          // CRC16 or simple checksum
}  __attribute__((packed)) ControlCmd;

typedef struct {
    uint8_t header1;              // 0xCD
    uint8_t header2;              // 0xEF

    uint16_t telemetry_seq;       // Stm32 packet counter
    uint16_t last_cmd_seq;        // Jetson packet counter

    uint32_t stm32_timestamp_ms;  // STM32 HAL_GetTick

    int32_t erpm;                 // VESC Status 1
    int16_t motor_current_x10;    // A * 10
    int16_t duty_x1000;           // duty * 1000

    uint16_t crc;                 // CRC16 
} __attribute__((packed)) Feedback;

class Car{
private:
public:
	void SetThrottle(float Value);
	void SetSteering(float Degree);    

};

