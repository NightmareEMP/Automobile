#include "vesc.h"
#include <stdint.h>
#include "main.h"
#include "perip_handles.h"

volatile uint32_t can_free;
volatile HAL_StatusTypeDef can_st;
volatile uint32_t can_state;
volatile uint32_t can_err;
volatile uint32_t can_mailbox;
static uint32_t g_tx_fail = 0;
static uint32_t g_tx_ok = 0;


void VESC_Subs2RPM(const uint16_t *throttle, uint16_t *throttle_RPM){
	uint16_t throttle_SBUS = *throttle;

	// Throttle (TODO)
	if(throttle_SBUS >=  TH_FULL_FORWARD && throttle_SBUS <=  TH_FULL_BACKWARD) {
		if(throttle_SBUS <= TH_IDLE_UPPER_BOUNDARY && throttle_SBUS >= TH_IDLE_LOWER_BOUNDARY) {
			*throttle_RPM = 0;
		}
		else {
			*throttle_RPM = 0;
		}
	}
	return;

}

void  VESC_Sbus2Current(const uint16_t *throttle, int16_t *throttle_CURR){
	if (throttle == NULL || throttle_CURR == NULL) {
	    return;
	}

	uint16_t throttle_SBUS = *throttle;

    if (throttle_SBUS >= TH_IDLE_LOWER_BOUNDARY && throttle_SBUS <= TH_IDLE_UPPER_BOUNDARY) {
    	*throttle_CURR = FULL_STOP_CURR;
    }
    else {
    	if (throttle_SBUS < TH_IDLE_LOWER_BOUNDARY) {
			float ratio = (float)(TH_IDLE_LOWER_BOUNDARY - throttle_SBUS) / (float)(TH_IDLE_LOWER_BOUNDARY - TH_FULL_FORWARD);

			 if (ratio > 1.0f) {
				 ratio = 1.0f;
			 }

			 *throttle_CURR = FULL_FORWARD_CURR * ratio;

    	}
    	else {
    		 float ratio = (float)(throttle_SBUS - TH_IDLE_UPPER_BOUNDARY)/ (float)(TH_FULL_BACKWARD - TH_IDLE_UPPER_BOUNDARY);

    		 if (ratio > 1.0f) {
    		     ratio = 1.0f;
    		 }

    		 *throttle_CURR =  FULL_BACKWARD_CURR * ratio ;
    	}

    }
    return;
}

void static VESC_buffer_append_int32(uint8_t* buffer, int32_t value) {
	buffer[0] = (value >> 24) & 0xFF;
	buffer[1] = (value >> 16) & 0xFF;
	buffer[2] = (value >> 8) & 0xFF;
	buffer[3] = value & 0xFF;
}

void VESC_SetCurrent_Brake(float current_A, const uint32_t vesc_id) {
	CAN_TxHeaderTypeDef txHeader;
	uint8_t data[4];
	uint32_t txMailbox;
	int32_t current_mA = (int32_t)(current_A * 1000.0f);

	txHeader.IDE = CAN_ID_EXT;
	txHeader.ExtId = (CAN_PACKET_SET_CURRENT_BRAKE << 8) | vesc_id;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = 4;
	txHeader.TransmitGlobalTime = DISABLE;


	// Store in buffer array
	VESC_buffer_append_int32(data, current_mA);

	can_free = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
	can_mailbox = txMailbox;
	can_state = HAL_CAN_GetState(&hcan1);
	can_err = HAL_CAN_GetError(&hcan1);
	return;
}

void VESC_SetCurrent(float current_A, const uint32_t vesc_id){
    CAN_TxHeaderTypeDef txHeader;
    uint8_t data[4];
    uint32_t txMailbox;
    int32_t current_mA = (int32_t)(current_A * 1000.0f);

    txHeader.IDE = CAN_ID_EXT;
    txHeader.ExtId = (CAN_PACKET_SET_CURRENT << 8) | vesc_id;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 4;
    txHeader.TransmitGlobalTime = DISABLE;

    // Store in buffer array
    VESC_buffer_append_int32(data, current_mA);

    can_free = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);

    HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
    can_mailbox = txMailbox;
    can_state = HAL_CAN_GetState(&hcan1);
    can_err = HAL_CAN_GetError(&hcan1);
}

void VESC_SetRPM(int32_t erpm, const uint32_t vesc_id){
    CAN_TxHeaderTypeDef txHeader;
    uint8_t data[4];
    uint32_t txMailbox;
    HAL_StatusTypeDef ret;

    txHeader.IDE = CAN_ID_EXT;
    txHeader.ExtId = (CAN_PACKET_SET_RPM << 8) | vesc_id;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 4;
    txHeader.TransmitGlobalTime = DISABLE;

    // Store in buffer array
    VESC_buffer_append_int32(data, erpm);

    ret = HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
    if(ret == HAL_OK){
    	//ok
    	g_tx_ok++;
    }
    else {
    	g_tx_fail++;
    }

}

void VESC_Feedback_PackAndSend(const volatile vesc_status_msg_1_t *msg){
	Feedback pkt;
	if(msg->valid == CTRL_OK){
		pkt.header1 = 0xCD;
		pkt.header2 = 0xEF;
		pkt.telemetry_seq = 0;
		pkt.last_cmd_seq = 0;

		pkt.stm32_timestamp_ms = msg->last_rx_ms;
		pkt.erpm =  msg->erpm;
		pkt.motor_current_x10 =  msg->current_x10;
		pkt.duty_x1000 = msg->duty_x1000;
		pkt.crc = 0;
		// send using uart1
		HAL_UART_Transmit(&huart1, (uint8_t *)&pkt, sizeof(pkt), 10);
	}
	return;

}

static int32_t VESC_Get_i32_be(uint8_t *data, int *idx){
    int32_t value =
        ((int32_t)data[*idx] << 24) |
        ((int32_t)data[*idx + 1] << 16) |
        ((int32_t)data[*idx + 2] << 8) |
        ((int32_t)data[*idx + 3]);

    *idx += 4;
    return value;
}

static int16_t VESC_Get_i16_be(uint8_t *data, int *idx){
    int16_t value =
        ((int16_t)data[*idx] << 8) |
        ((int16_t)data[*idx + 1]);

    *idx += 2;
    return value;
}


void VESC_DecodeStatus1(uint8_t controller_id, uint8_t *data, volatile vesc_status_msg_1_t *msg){
    int idx = 0;

    int32_t erpm = VESC_Get_i32_be(data, &idx);
    int16_t current_x10 = VESC_Get_i16_be(data, &idx);
    int16_t duty_x1000 = VESC_Get_i16_be(data, &idx);

    msg->controller_id = controller_id;
    msg->erpm = erpm;
    msg->current_x10 = current_x10;
    msg->duty_x1000 = duty_x1000;
    msg->last_rx_ms = HAL_GetTick();
    msg->valid = CTRL_OK;
}

