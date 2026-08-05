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