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
    uint16_t throttle;
    uint16_t steering;
    uint8_t valid;
    uint32_t last_update_ms;
} ControlInput;

// VESC feedback
#define CAN_PACKET_STATUS_1 (9U)
typedef struct {
    uint8_t controller_id;
    int32_t erpm;
    int16_t current_x10;
    int16_t duty_x1000;
    uint32_t last_rx_ms;
    uint8_t valid;
} vesc_status_msg_1_t;

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
volatile uint32_t can_free;
volatile HAL_StatusTypeDef can_st;
volatile uint32_t can_state;
volatile uint32_t can_err;
volatile uint32_t can_mailbox;

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

static uint32_t vesc_id = 1;
volatile vesc_status_msg_1_t g_vesc_status1;
volatile uint32_t g_can_rx_count = 0;
volatile uint32_t g_last_ext_id = 0;
static uint32_t g_tx_fail = 0;
static uint32_t g_tx_ok = 0;

void static buffer_append_int32(uint8_t* buffer, int32_t value) {
	buffer[0] = (value >> 24) & 0xFF;
	buffer[1] = (value >> 16) & 0xFF;
	buffer[2] = (value >> 8) & 0xFF;
	buffer[3] = value & 0xFF;
}

void VESC_SetCurrent_Brake(float current_A) {
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
	buffer_append_int32(data, current_mA);

	can_free = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
	can_mailbox = txMailbox;
	can_state = HAL_CAN_GetState(&hcan1);
	can_err = HAL_CAN_GetError(&hcan1);
	return;
}
void VESC_SetCurrent(float current_A)
{
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
    buffer_append_int32(data, current_mA);

    can_free = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);

    HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
    can_mailbox = txMailbox;
    can_state = HAL_CAN_GetState(&hcan1);
    can_err = HAL_CAN_GetError(&hcan1);
}

void VESC_SetRPM(int32_t erpm)
{
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
    buffer_append_int32(data, erpm);

    ret = HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
    if(ret == HAL_OK){
    	//ok
    	g_tx_ok++;
    }
    else {
    	g_tx_fail++;
    }

}

void VESC_Feedback_PackAndSend(void){
	Feedback pkt;
	if(g_vesc_status1.valid == CTRL_OK){
		pkt.header1 = 0xCD;
		pkt.header2 = 0xEF;
		pkt.telemetry_seq = 0;
		pkt.last_cmd_seq = 0;

		pkt.stm32_timestamp_ms = g_vesc_status1.last_rx_ms;
		pkt.erpm = g_vesc_status1.erpm;
		pkt.motor_current_x10 = g_vesc_status1.current_x10;
		pkt.duty_x1000 = g_vesc_status1.duty_x1000;
		pkt.crc = 0;
		// send using uart1
		HAL_UART_Transmit(&huart1, (uint8_t *)&pkt, sizeof(pkt), 10);
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

  (void*)HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
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
//  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1520);
  VESC_SetRPM(0);
  HAL_Delay(1000);

  while (1)
  {



	  uint32_t now = HAL_GetTick();


	  // Set RPM to 1000 every 10 ms
	  VESC_SetRPM(1000);


	  // Receeive ERPM feedback every 20ms
	  if ((uint32_t)(now - last_feedback_ms) >= 20U){
		  last_feedback_ms = now;
		  VESC_Feedback_PackAndSend();
	  }


	  HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
static int32_t VESC_Get_i32_be(uint8_t *data, int *idx)
{
    int32_t value =
        ((int32_t)data[*idx] << 24) |
        ((int32_t)data[*idx + 1] << 16) |
        ((int32_t)data[*idx + 2] << 8) |
        ((int32_t)data[*idx + 3]);

    *idx += 4;
    return value;
}

static int16_t VESC_Get_i16_be(uint8_t *data, int *idx)
{
    int16_t value =
        ((int16_t)data[*idx] << 8) |
        ((int16_t)data[*idx + 1]);

    *idx += 2;
    return value;
}


void VESC_DecodeStatus1(uint8_t controller_id, uint8_t *data)
{
    int idx = 0;

    int32_t erpm = VESC_Get_i32_be(data, &idx);
    int16_t current_x10 = VESC_Get_i16_be(data, &idx);
    int16_t duty_x1000 = VESC_Get_i16_be(data, &idx);

    g_vesc_status1.controller_id = controller_id;
    g_vesc_status1.erpm = erpm;
    g_vesc_status1.current_x10 = current_x10;
    g_vesc_status1.duty_x1000 = duty_x1000;
    g_vesc_status1.last_rx_ms = HAL_GetTick();
    g_vesc_status1.valid = CTRL_OK;
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

    g_can_rx_count++;
    g_last_ext_id = rxHeader.ExtId;

    if (rxHeader.IDE != CAN_ID_EXT) {
        return;
    }

    uint8_t cmd = (rxHeader.ExtId >> 8) & 0xFF;
    uint8_t id  = rxHeader.ExtId & 0xFF;

    // Store Feedback data
    if (cmd == CAN_PACKET_STATUS_1 && id == vesc_id && rxHeader.DLC == 8) {
        VESC_DecodeStatus1(id, rxData);
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
  sConfigOC.Pulse = 0;
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
