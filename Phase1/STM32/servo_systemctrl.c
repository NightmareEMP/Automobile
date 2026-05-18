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
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CTRL_OK 0U
#define CTRL_NG 1U
// TH ST Sbus Idle value tolerance
#define TH_IDLE_UPPER_BOUNDARY 1025U  // F 8
#define TH_IDLE_LOWER_BOUNDARY 1015U
#define ST_IDLE_UPPER_BOUNDARY 1045U  // R 10
#define ST_IDLE_LOWER_BOUNDARY 1035U
// TH ST Sbus max min value
#define TH_FULL_FORWARD 300U
#define TH_FULL_BACKWARD 1745U
#define ST_FULL_RIGHT 310U
#define ST_FULL_LEFT 1740U
// Servo
#define CENTER 1520U
#define FULL_LEFT 1300U
#define FULL_RIGHT 1740U

// Jetson Packet Headers
#define HEADER_FIRST 0xAB
#define HEADER_SECOND 0x55



#define SBUS_TIMEOUT_MS 100
#define JETSON_TIMEOUT_MS 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
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
/* USER CODE BEGIN PFP */
typedef struct  {
    uint8_t  header1;      // 0xAB
    uint8_t  header2;      // 0x55
    int16_t  steering;     //
    int16_t  throttle;     //
    uint8_t  mode;         // 0=manual, 1=auto, 2=estop
    uint8_t  seq;          // packet counter
    uint16_t crc;          // CRC16 or simple checksum
}  __attribute__((packed)) ControlCmd;

typedef struct {
    uint16_t throttle;
    uint16_t steering;
    uint8_t valid;
    uint32_t last_update_ms;
} ControlInput;

/* Global Variables */
#define BUFFER_SIZE 50U
#define JETSON_BUFFER_SIZE sizeof(ControlCmd)*20

uint8_t sbus_buffer_ready[BUFFER_SIZE];
uint8_t jetson_buffer_ready[JETSON_BUFFER_SIZE];

// manual control
volatile uint8_t manual_flag = 0;
volatile uint16_t jetson_last_pos = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static uint16_t map_range(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Subs2PWM(const uint16_t *throttle, const uint16_t *steering, uint16_t *throttle_PWM, uint16_t *steering_PWM){
	uint16_t throttle_SBUS = *throttle;
	uint16_t steering_SBUS = *steering;
	// Throttle (TODO)
	if(throttle_SBUS >=  TH_FULL_FORWARD && throttle_SBUS <=  TH_FULL_BACKWARD) {
		if(throttle_SBUS <= TH_IDLE_UPPER_BOUNDARY && throttle_SBUS >= TH_IDLE_LOWER_BOUNDARY) {
			*throttle_PWM = 0;
		}
		else {
			*throttle_PWM = 0;
		}
	}
	// Steering
	if(steering_SBUS >= ST_FULL_RIGHT && steering_SBUS <= ST_FULL_LEFT){
		if(steering_SBUS <= ST_IDLE_UPPER_BOUNDARY && steering_SBUS >= ST_IDLE_LOWER_BOUNDARY) {
			*steering_PWM = CENTER;
		}
		else {
			// Right
			if (steering_SBUS > ST_IDLE_UPPER_BOUNDARY) {

				*steering_PWM = map_range(steering_SBUS, ST_IDLE_UPPER_BOUNDARY, ST_FULL_LEFT, CENTER, FULL_LEFT);
			}
			// left
			else {
				*steering_PWM = map_range(steering_SBUS, ST_FULL_RIGHT, ST_IDLE_LOWER_BOUNDARY, FULL_RIGHT, CENTER);
			}
		}
	}
	return;

}

void JetsonParserFeed(uint8_t byte, ControlInput *Data)
{
    static uint8_t pkt_buf[sizeof(ControlCmd)];
    static uint8_t pkt_idx = 0;

    if (pkt_idx == 0) {
        if (byte == 0xAB) {
            pkt_buf[pkt_idx++] = byte;
        }
        return;
    }

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
void JetsonControl(ControlInput *Data){
	uint16_t curr_pos = JETSON_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);

	if (curr_pos > jetson_last_pos) {
		for (uint16_t i = jetson_last_pos; i < curr_pos; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}
	}
	else {
		for (uint16_t i = jetson_last_pos; i < JETSON_BUFFER_SIZE; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}

		for (uint16_t i = 0; i < curr_pos; i++) {
			JetsonParserFeed(jetson_buffer_ready[i], Data);
		}
	}
	jetson_last_pos = curr_pos;
	return;

}
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

	// Data Valid
	if (header_index != -1 && footer_index != -1) {
		// Extract ST/TH
		steering_sbus = ((local_copy[(header_index + 1) % BUFFER_SIZE] |
					  local_copy[(header_index + 2) % BUFFER_SIZE] << 8) & 0x07FF);
		throttle_sbus = ((local_copy[(header_index + 2) % BUFFER_SIZE] >> 3 |
					  local_copy[(header_index + 3) % BUFFER_SIZE] << 5) & 0x07FF);

		// low pass filter  (TODO) : currently jittering
		static uint16_t steering_filtered = CENTER;

		steering_filtered =
		    (steering_filtered * 7 + Data->steering * 1) / 8;

		Data->steering = steering_filtered;

		// Fill in Data
		Subs2PWM(&throttle_sbus, &steering_sbus, &(Data->throttle), &(Data->steering));
		Data->valid = CTRL_OK;
		Data->last_update_ms = HAL_GetTick();
	// For Debug
//	 uint8_t msg[4];
//	 memcpy(msg, (uint8_t*)&(throttle_sbus), 2);
//	 memcpy(msg+2, (uint8_t*)&(steering_sbus), 2);
//	 HAL_UART_Transmit(&huart1, msg, 4, 10);
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
   uint16_t throttle_execute = 0U;
   uint16_t steering_execute = CENTER;
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
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_UART_Receive_DMA(&huart6, sbus_buffer_ready, BUFFER_SIZE);
  HAL_UART_Receive_DMA(&huart1, jetson_buffer_ready, JETSON_BUFFER_SIZE);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1520);
  HAL_Delay(1000);
  while (1)
  {
	  // Poll SBUS signal
	  ManualControl(&manual_input);
	  // Check timeout 100ms
	  if( HAL_GetTick() - manual_input.last_update_ms <= SBUS_TIMEOUT_MS) {
		  // Idle or not
		  if (manual_input.steering == CENTER && manual_input.throttle == 0) {
			  // current do not thing if idle
		  }
		  else {
			  // Set to Manual Mode
			  manual_flag = 1;
		  }
	  }
	  else {
		  // SBUS notworking
		  manual_input.valid = CTRL_NG;
	  }
	  // Poll Jetson Signal
	  JetsonControl(&jetson_input);

	  // Check timeout 100ms
	  if( HAL_GetTick() - jetson_input.last_update_ms <= JETSON_TIMEOUT_MS) {

	  }
	  else {
		  jetson_input.valid = CTRL_NG;
	  }



	  if(manual_flag == 1) {
		  steering_execute = manual_input.steering;
		  throttle_execute = 0;
	  }
	  else if(jetson_input.valid == CTRL_OK){
		  steering_execute = jetson_input.steering;
		  throttle_execute = jetson_input.throttle;
	  }
	  else {
		  // use what idle manual status
		  steering_execute = CENTER;
		  throttle_execute = CENTER;
	  }

	  // Control Servo
//	  uint8_t msg[4];
//	  memcpy(msg, (uint8_t*)(&throttle_execute), 2);
//	  memcpy(msg+2, (uint8_t*)(&steering_execute), 2);
//	  HAL_UART_Transmit(&huart1, msg, 4, 1);
	  if(steering_execute > CENTER) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  // Control Motor
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, steering_execute);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == B1_Pin) {
        manual_flag = 0;
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
  sConfigOC.Pulse = 1520;
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
