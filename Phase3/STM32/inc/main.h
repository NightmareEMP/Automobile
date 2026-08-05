/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define CTRL_OK 0U
#define CTRL_NG 1U
// TH ST Sbus Idle value tolerance
#define TH_IDLE_LOWER_BOUNDARY  1005U // F 8
#define TH_IDLE_UPPER_BOUNDARY  1030U
#define ST_IDLE_UPPER_BOUNDARY 1045U  // R 10
#define ST_IDLE_LOWER_BOUNDARY 1035U
// TH ST Sbus max min value
#define TH_FULL_FORWARD 300U
#define TH_FULL_BACKWARD 1745U
#define ST_FULL_RIGHT 310U
#define ST_FULL_LEFT 1740U


// Jetson Packet Headers
#define HEADER_FIRST 0xAB
#define HEADER_SECOND 0x55

#define SBUS_TIMEOUT_MS 100
#define JETSON_TIMEOUT_MS 200

// SBUS Buffer size
#define BUFFER_SIZE 50U
// Jetson CMD Buffer size
#define JETSON_BUFFER_SIZE sizeof(ControlCmd)*(40)

#define SUBS_JITTER_COMPEN (8)

typedef struct  {
    uint8_t  header1;      // 0xAB
    uint8_t  header2;      // 0x55
    int16_t  steering;     //
    int16_t  throttle;     // manual: mA, auto: rpm
    uint8_t  mode;         // 0=manual, 1=auto, 2=estop
    uint8_t  seq;          // packet counter
    uint16_t crc;          // CRC16 or simple checksum
}  __attribute__((packed)) ControlCmd;

typedef struct {
    uint8_t header1;              // 0xCD
    uint8_t header2;              // 0xEF

    uint16_t telemetry_seq;       // STM32 packet counter
    uint16_t last_cmd_seq;        // Jetson packet counter, first test can be 0

    uint32_t stm32_timestamp_ms;  // HAL_GetTick()

    int32_t erpm;                 // VESC Status 1 actual ERPM
    int16_t motor_current_x10;    // A * 10
    int16_t duty_x1000;           // duty * 1000

    uint16_t crc;                 // CRC16, first test can be 0
} __attribute__((packed)) Feedback;

typedef struct {
    int16_t throttle;
    uint16_t steering;
    uint8_t valid;
    uint32_t last_update_ms;
} ControlInput;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
