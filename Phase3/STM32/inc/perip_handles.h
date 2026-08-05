#ifndef PERRIP_HANDLES_H
#define PERRIP_HANDLES_H

#include "main.h"


extern CAN_HandleTypeDef hcan1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart6_rx;

#endif
