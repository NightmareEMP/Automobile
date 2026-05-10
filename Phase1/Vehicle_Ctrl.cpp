#include <cstdio>
#include <cstring>
#include <cmath>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "Vehicle_Ctrl.h"
#include <Uart_drv.hpp>
#include <vector>

#define CONTROL_CMD_PACKET_SIZE sizeof(ControlCmd)

#define  CENTER 1520
#define FULL_LEFT 1320
#define FULL_RIGHT 1720
void EnvCheck(void){
    static_assert(sizeof(ControlCmd) == 10, "ControlCmd must be 10 bytes");
    return;
}
int main(){
    // Env Check
    EnvCheck();

    // Create Uart 
    Uart_Jetson Uart;

    if (!Uart.openPort("/dev/ttyTHS1", 115200)) {
        std::cerr << "Failed to open UART\n";
        return 1;
    }
    // Create msg 
    ControlCmd cmd{};
    std::vector<int16_t> dir(4);
    dir[1] = 1720;
    dir[0] = 1520;
    dir[2] = 1520;
    dir[3] = 1320;
    uint32_t idx = 0;
    cmd.header1 = 0xAB;
    cmd.header2 = 0x55;
    cmd.steering = 1700;
    cmd.throttle = 1420;
    cmd.mode = 1;
    cmd.seq = 1;
    cmd.crc = 0;

    uint8_t tx_buf[CONTROL_CMD_PACKET_SIZE];
    uint8_t rx_buf[4];
    while(1){
        cmd.steering = dir[idx++];
        idx%=4;
        memset(tx_buf, 0, CONTROL_CMD_PACKET_SIZE);
        memset(rx_buf, 0, 4);
        memcpy(tx_buf, &cmd, CONTROL_CMD_PACKET_SIZE);

        size_t total_write = 0;
        while (total_write < CONTROL_CMD_PACKET_SIZE) {
            int n = Uart.writeBytes(tx_buf + total_write, CONTROL_CMD_PACKET_SIZE - total_write);
            if (n < 0) {
                std::cerr << "read failed\n";
                return 1;
            }
            if (n == 0) {
                continue;
            }
            total_write += n;
        }
        sleep(1);
        // std::cout<<"Sent Done\n";
        // usleep(20000); // 20 ms
        // size_t total_read = 0;
        // while (total_read < 4) {
        //     int n = Uart.readBytes(rx_buf + total_read, 4 - total_read);
        //     if (n < 0) {
        //         std::cerr << "read failed\n";
        //         return 1;
        //     }
        //     if (n == 0) {
        //         continue;
        //     }
        //     total_read += n;
        // }
    
        // if (total_read == 4) {
        //     uint16_t steering = 0;
        //     uint16_t throttle = 0;
        //     memcpy(&throttle, &rx_buf[0], 2);
        //     memcpy(&steering, &rx_buf[2], 2);

        //     printf("steering = %u, throttle = %u\n", steering, throttle);
        // } else {
        //     printf("incomplete packet\n");
        // }
    }


    return 0;
}