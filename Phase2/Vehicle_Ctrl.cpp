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
#define FEEDBACK_PACKET_SIZE sizeof(Feedback)

#define  CENTER 1520
#define FULL_LEFT 1320
#define FULL_RIGHT 1720
void EnvCheck(void){
    // Check packet size
    static_assert(CONTROL_CMD_PACKET_SIZE == 10, "ControlCmd must be 10 bytes");
    static_assert(FEEDBACK_PACKET_SIZE == 20, "Feedback must be 20 bytes");
    return;
}
int main(){
    // Check Env
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
    uint8_t rx_buf[FEEDBACK_PACKET_SIZE];
    while(1){
        // std::cout<<"Recive start\n";
        size_t total_read = 0;
        memset(rx_buf, 0, FEEDBACK_PACKET_SIZE);
        while (total_read < FEEDBACK_PACKET_SIZE) {
            int n = Uart.readBytes(rx_buf + total_read, FEEDBACK_PACKET_SIZE - total_read);
            if (n < 0) {
                std::cerr << "read failed\n";
                return 1;
            }
            if (n == 0) {
                continue;
            }
            total_read += n;
        }
    
        if (total_read == FEEDBACK_PACKET_SIZE) {
            Feedback *pkt;
            pkt = (Feedback*)rx_buf;
            if (pkt->header1 == 0xCD && pkt->header2 == 0xEF) {
                printf("erpm = %d, fail = %d\n", pkt->erpm, pkt->stm32_timestamp_ms);
            }
        } else {
            printf("incomplete packet\n");
        }
    }

    return 0;
}