/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "servo.h"
#include "vesc.h"
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart6_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_CAN1_Init(void);
/* USER CODE BEGIN PFP */

/* Global Variables */

uint8_t sbus_buffer_ready[BUFFER_SIZE];
uint8_t jetson_buffer_ready[JETSON_BUFFER_SIZE];

// manual control
volatile uint8_t manual_flag = 0;
// Pos for jetson's dma ring buffer
volatile uint16_t jetson_last_pos = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static const uint32_t vesc_id = 1;
volatile vesc_status_msg_1_t g_vesc_status1;
volatile uint32_t g_last_ext_id = 0;


// Parse Jetson packet
void JetsonParserFeed(uint8_t byte, ControlInput *Data)
{
    static uint8_t pkt_buf[sizeof(ControlCmd)];
    static uint8_t pkt_idx = 0;

    // Check Header 1
    if (pkt_idx == 0) {
        if (byte == 0xAB) {
            pkt_buf[pkt_idx++] = byte;
        }
        return;
    }
    // Check Header 2
    if (pkt_idx == 1) {
        if (byte == 0x55) {
            pkt_buf[pkt_idx++] = byte;
        } else {
            pkt_idx = 0;
        }
        return;
    }

    pkt_buf[pkt_idx++] = byte;

    if (pkt_idx == sizeof(ControlCmd)) {
        ControlCmd pkt;
        memcpy(&pkt, pkt_buf, sizeof(ControlCmd));

        Data->throttle = pkt.throttle;
        Data->steering = pkt.steering;
        Data->valid = CTRL_OK;
        Data->last_update_ms = HAL_GetTick();

        pkt_idx = 0;
    }

}
// Get Jetson data
void JetsonControl(ControlInput *Data){
	uint16_t curr_pos = JETSON_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);

	if (curr_pos > jetson_last_pos) {
		for (uint16_t i = jetson_last_pos; i < curr_pos; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}
	}
	else if (curr_pos < jetson_last_pos){
		for (uint16_t i = jetson_last_pos; i < JETSON_BUFFER_SIZE; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}

		for (uint16_t i = 0; i < curr_pos; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}
	}
	else{
		// Idle or disconnect (Warning: might have issue that if stm32 is using too much time resulting curr_pos == jetson_last_pos while jetson acutally not timeout
		// Adjust JETSON_BUFFER_SIZE to fix, or use HAL_UART_RxHalfCpltCallback
	}
	jetson_last_pos = curr_pos;
	return;

}
// Record last data
volatile uint16_t last_servo = 0;
volatile int16_t last_vesc = 0;


static void InitState(void){
   __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, CENTER);
   VESC_SetRPM(FULL_STOP, vesc_id);
   HAL_Delay(1000);
}

// Get Transmitter data
void ManualControl(ControlInput *Data){
	uint8_t local_copy[BUFFER_SIZE];
	uint16_t steering_sbus;
	uint16_t throttle_sbus;

	// Clear Overrun Errors immediately
	if (__HAL_UART_GET_FLAG(&huart6, UART_FLAG_ORE)) {
		  __HAL_UART_CLEAR_OREFLAG(&huart6);
	}

	// Copy to local copy preventing from overrun
	memcpy(local_copy, (uint8_t*)sbus_buffer_ready, BUFFER_SIZE);

	int header_index = -1;
	int footer_index = -1;
	// Check data frame valid
	for (int i = 0; i < BUFFER_SIZE; i++) {
		if (local_copy[i] == 0x0F && local_copy[(i + 24) % BUFFER_SIZE] == 0x00) {
			uint8_t flags = local_copy[(i + 23) % BUFFER_SIZE];

			if (!(flags & 0x08) && !(flags & 0x04)) { // ONLY process if failsafe is NOT active
				header_index = i;
				footer_index = (i + 24) % BUFFER_SIZE;
				break;
			}
		}
	}

	for (int i = 0; i < BUFFER_SIZE; i++)
	{
	    if (local_copy[i] != 0x0F)
	        continue;


	    int footer = (i + 24) % BUFFER_SIZE;
	    // Check footer
	    uint8_t footer_byte = local_copy[footer];

	    uint16_t footer_valid =
	        footer_byte == 0x00 ||
	        footer_byte == 0x04 ||
	        footer_byte == 0x14 ||
	        footer_byte == 0x24 ||
	        footer_byte == 0x34;

	    if (footer_valid == 0)
	        continue;


	    uint8_t flags = local_copy[(i + 23) % BUFFER_SIZE];

	    if ((flags & 0x0C) != 0)
	        continue;



	    header_index = i;
	    footer_index = footer;
	    break;
	}

	// Data Valid
	if (header_index != -1 && footer_index != -1) {
		// Extract ST/TH
		steering_sbus = ((local_copy[(header_index + 1) % BUFFER_SIZE] |
					  local_copy[(header_index + 2) % BUFFER_SIZE] << 8) & 0x07FF);
		throttle_sbus = ((local_copy[(header_index + 2) % BUFFER_SIZE] >> 3 |
					  local_copy[(header_index + 3) % BUFFER_SIZE] << 5) & 0x07FF);


		// Update value if receive action, and filter sbus value jitter
		Servo_Subs2PWM(&steering_sbus, &(Data->steering));

		if( Data->steering != CENTER && abs(Data->steering - last_servo) <= SUBS_JITTER_COMPEN) {
			Data->steering = last_servo;
		}

		VESC_Sbus2Current(&throttle_sbus, &(Data->throttle));

//		if( Data->throttle != FULL_STOP_CURR && abs(Data->throttle - last_vesc) <= SUBS_JITTER_COMPEN) {
//			Data->throttle = last_vesc;
//		}

		last_servo = Data->steering;
		last_vesc = Data->throttle;
		Data->valid = CTRL_OK;
		Data->last_update_ms = HAL_GetTick();
		// For Debug
		//  uint8_t msg[4];
		//  memcpy(msg, (uint8_t*)&(Data->throttle), 2);
		//  memcpy(msg+2, (uint8_t*)&(Data->steering), 2);
		//  HAL_UART_Transmit(&huart1, msg, 4, 10);
//	  if(Data->steering > CENTER) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//	  else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}

	  return;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
volatile uint32_t button_count = 0;
int main(void)
{
  /* USER CODE BEGIN 1 */
   ControlInput manual_input = {
       .throttle = 0,
       .steering = CENTER,
       .valid = 0,
       .last_update_ms = 0
   };
   ControlInput jetson_input = {
       .throttle = 0,
       .steering = CENTER,
       .valid = 0,
       .last_update_ms = 0
   };
   // Final Execute value
   int16_t throttle_execute = 0U;
   uint16_t steering_execute = CENTER;

   static uint32_t last_feedback_ms = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_USART6_UART_Init();
  MX_CAN1_Init();

  /* USER CODE BEGIN 2 */
  CAN_FilterTypeDef filter;
  filter.FilterBank = 0;
  filter.FilterMode = CAN_FILTERMODE_IDMASK;
  filter.FilterScale = CAN_FILTERSCALE_32BIT;
  filter.FilterIdHigh = 0x0000;
  filter.FilterIdLow = 0x0000;
  filter.FilterMaskIdHigh = 0x0000;
  filter.FilterMaskIdLow = 0x0000;
  filter.FilterFIFOAssignment = CAN_RX_FIFO0;
  filter.FilterActivation = ENABLE;
  filter.SlaveStartFilterBank = 14;

  // CAN (motor)
  HAL_CAN_ResetError(&hcan1);
  if (HAL_CAN_ConfigFilter(&hcan1, &filter) != HAL_OK) {
      Error_Handler();
  }

  if (HAL_CAN_Start(&hcan1) != HAL_OK) {
      Error_Handler();
  }

  (void)HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
//
//  g_can_ier = hcan1.Instance->IER;
//  g_nvic_enabled = NVIC_GetEnableIRQ(CAN1_RX0_IRQn);


//  NVIC_SetPendingIRQ(CAN1_RX0_IRQn);
  HAL_Delay(100);
  // PWM (servo)
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  // UART (Jetson, Transmitter)
  HAL_UART_Receive_DMA(&huart6, sbus_buffer_ready, BUFFER_SIZE);
  HAL_UART_Receive_DMA(&huart1, jetson_buffer_ready, JETSON_BUFFER_SIZE);

  // Set Servo and motor to idle
   InitState();
  while (1)
  {
//
	  ManualControl(&manual_input);

	  uint32_t now = HAL_GetTick();// Check timeout 100ms

	  if( HAL_GetTick() - manual_input.last_update_ms <= SBUS_TIMEOUT_MS) {
		  // Idle or not
		  if (manual_input.steering == CENTER && manual_input.throttle == FULL_STOP_CURR) {
			  // current do not thing if idle
		  }
		  else {
			  // Set to Manual Mode
			  manual_flag = 1;
		  }
	  }
	  else {
		  // SBUS notworking or didn't turn on trasmitter 
		  manual_input.valid = CTRL_NG;
		  manual_flag = 1;
		  manual_input.steering = CENTER;
		  manual_input.throttle = FULL_STOP_CURR;

	  }



	  JetsonControl(&jetson_input);
	  // If Jetson is timeout, set idle
	  if ((uint32_t)(now - jetson_input.last_update_ms) > JETSON_TIMEOUT_MS) {
		  jetson_input.steering = CENTER;
		  jetson_input.throttle = FULL_STOP;
	  }

    // Check if manaul interrupts
	  if(manual_flag == 1) {
		  steering_execute = manual_input.steering;
		  throttle_execute = manual_input.throttle;
	  }
	  else if(jetson_input.valid == CTRL_OK){
		  steering_execute = jetson_input.steering;
		  throttle_execute = jetson_input.throttle;
	  }
	  else {
		  // use what idle manual status
		  steering_execute = CENTER;
		  throttle_execute = FULL_STOP_CURR;
	  }

    if (manual_flag) {
      // Manual Control motor use current mode
       float throttle_execute_f = (float)throttle_execute / (float)1000;
	     VESC_SetCurrent(throttle_execute_f,vesc_id);

       // servo
       __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, steering_execute);
    }
    else {
       // Jetson Control motor use rpm mode
       VESC_SetRPM(throttle_execute, vesc_id);
       // Servo
       __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, steering_execute);

    }
// For Debug
//    uint8_t msg[4];
//		 memcpy(msg, (uint8_t*)&(throttle_execute), 2);
//		 memcpy(msg+2, (uint8_t*)&(steering_execute), 2);
//		 HAL_UART_Transmit(&huart1, msg, 4, 10);
//

	  // Receeive ERPM feedback every 20ms
	  if ((uint32_t)(now - last_feedback_ms) >= 20U){
		  last_feedback_ms = now;
		  VESC_Feedback_PackAndSend(&g_vesc_status1);
	  }

	  HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == B1_Pin) {
    	button_count++;
        manual_flag = 0;
    }
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];

    if (hcan->Instance != CAN1) {
        return;
    }

    // Get Feedback
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK) {
        return;
    }

    g_last_ext_id = rxHeader.ExtId;

    if (rxHeader.IDE != CAN_ID_EXT) {
        return;
    }

    uint8_t cmd = (rxHeader.ExtId >> 8) & 0xFF;
    uint8_t id  = rxHeader.ExtId & 0xFF;

    // Store Feedback data
    if (cmd == CAN_PACKET_STATUS_1 && id == vesc_id && rxHeader.DLC == 8) {
        VESC_DecodeStatus1(id, rxData, &g_vesc_status1);
    }
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
// LOOPBACK for Debug Usage
//  hcan1.Init.Mode = CAN_MODE_LOOPBACK;

  hcan1.Init.SyncJumpWidth = CAN_SJW_4TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;


  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;


  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 89;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 3002;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = CENTER;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 100000;
  huart6.Init.WordLength = UART_WORDLENGTH_9B;
  huart6.Init.StopBits = UART_STOPBITS_2;
  huart6.Init.Parity = UART_PARITY_EVEN;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
