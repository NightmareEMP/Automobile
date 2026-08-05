#ifndef VESC_H
#define  VESC_H
#include <stdint.h>
#include "stm32f4xx_hal.h"
// VESC feedback
#define CAN_PACKET_STATUS_1 (9U)
#define FULL_BACKWARD (-3000)
#define FULL_FORWARD (3000)
#define FULL_STOP (0)

#define FULL_BACKWARD_CURR  (-4000)  // mA
#define FULL_FORWARD_CURR   (4000)
#define FULL_STOP_CURR      (0)

typedef struct {
    uint8_t controller_id;
    int32_t erpm;
    int16_t current_x10;
    int16_t duty_x1000;
    uint32_t last_rx_ms;
    uint8_t valid;
} vesc_status_msg_1_t;

// All Types of VESC Feedback
typedef enum {
	CAN_PACKET_SET_DUTY = 0,
	CAN_PACKET_SET_CURRENT,
	CAN_PACKET_SET_CURRENT_BRAKE,
	CAN_PACKET_SET_RPM,
	CAN_PACKET_SET_POS,
	CAN_PACKET_SET_CURRENT_REL = 10,
	CAN_PACKET_SET_CURRENT_BRAKE_REL,
	CAN_PACKET_SET_CURRENT_HANDBRAKE,
	CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
	CAN_PACKET_MAKE_ENUM_32_BITS = 0xFFFFFFFF,
} CAN_PACKET_ID;


void VESC_SetCurrent_Brake(float current_A, const uint32_t vesc_id);
void VESC_SetCurrent(float current_A, const uint32_t vesc_id);
void VESC_SetRPM(int32_t erpm, const uint32_t vesc_id);
void VESC_Feedback_PackAndSend(const volatile vesc_status_msg_1_t *msg);
void VESC_DecodeStatus1(uint8_t controller_id, uint8_t *data, volatile vesc_status_msg_1_t *msg);


#endif /*  VESC */
