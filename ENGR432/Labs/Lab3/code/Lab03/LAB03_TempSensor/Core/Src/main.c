/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "string.h"
#include "stm32f4xx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define RS 14
#define RW 12
#define EN 10
#define DB4 14 
#define DB5 15
#define DB6 13
#define DB7 14

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart4_rx;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ETH_Init(void);
static void MX_UART4_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LCD_port_init(int x);
void LCD_init(void);
void LCD_sendData(unsigned int bits);
void LCD_sendData(unsigned int bits);
void LCD_sendInstr(unsigned int high, unsigned int low);
void place_LCD_cursor(int num);
void delay(int num);
void setBits(char);
void intToChar(int num);
void doubleToLCD(double num, int sigfig);
void clear_pin(int pin);
void set_pin(int pin);
void check_BF(void);
void switch_line(int line);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_ETH_Init();
  MX_UART4_Init();
  MX_USB_OTG_FS_PCD_Init();
	LCD_init();
	place_LCD_cursor(1);
  /* USER CODE BEGIN 2 */
	uint8_t pdata[10];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		HAL_UART_Receive(&huart4, pdata, 8, 1000);
		LCD_sendData(pdata[0]);
		
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void LCD_init() {
	// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; //STEP 1: Enable GPIO in RCC AHB1ENR register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	
	GPIOG->MODER &= ~(3u << DB4*2); 
	GPIOF->MODER &= ~(3u << DB5*2); 
	GPIOE->MODER &= ~(3u << DB6*2); 
	GPIOF->MODER &= ~(3u << DB7*2); 
	GPIOE->MODER &= ~(3u << EN*2); 
	GPIOE->MODER &= ~(3u << RS*2);
	GPIOE->MODER &= ~(3u << RW*2);

	
	GPIOG->MODER |= (1u << DB4*2); 
	GPIOF->MODER |= (1u << DB5*2); 
	GPIOE->MODER |= (1u << DB6*2); 
	GPIOF->MODER |= (1u << DB7*2); 
	GPIOE->MODER |= (1u << EN*2); 
	GPIOE->MODER |= (1u << RS*2);
	GPIOE->MODER |= (1u << RW*2);
	

	GPIOG->PUPDR &= ~(1u << DB4); 
	GPIOF->PUPDR &= ~(1u << DB5); 
	GPIOE->PUPDR &= ~(1u << DB6); 
	GPIOF->PUPDR &= ~(1u << DB7); 
	GPIOE->PUPDR &= ~(1u << EN); 
	GPIOE->PUPDR &= ~(1u << RS); 
	GPIOE->PUPDR &= ~(1u << RW);
	

	//initialize
	clear_pin(RW);
	clear_pin(RS);
	check_BF();
	
	LCD_sendInstr(3,3);
	LCD_sendInstr(3,2);
	
	
	LCD_sendInstr(0x2,0x8);
	LCD_sendInstr(0x0,0x8);
	LCD_sendInstr(0x0,0x1);
	LCD_sendInstr(0x0,0x6);
	LCD_sendInstr(0x0,0xf);

	
}


void LCD_sendData(unsigned int bits){
	unsigned int high;
	unsigned int low;
	
	high = bits&0xf0U;
	high = high/16;
	low = bits&0xfU;
	
	set_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(high&0x1U<<DB4); //set
	GPIOF->ODR|=(high&0x2U<<(DB5-1)); //set
	GPIOE->ODR|=(high&0x4U<<(DB6-2)); //set
	GPIOF->ODR|=(high&0x8U<<(DB7-3)); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();

	set_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(low&0x1U<<DB4); //set
	GPIOF->ODR|=(low&0x2U<<(DB5-1)); //set
	GPIOE->ODR|=(low&0x4U<<(DB6-2)); //set
	GPIOF->ODR|=(low&0x8U<<(DB7-3)); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();
}

void LCD_sendInstr(unsigned int high, unsigned int low){
	clear_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(high&0x1U<<DB4); //set
	GPIOF->ODR|=(high&0x2U<<(DB5-1)); //set
	GPIOE->ODR|=(high&0x4U<<(DB6-2)); //set
	GPIOF->ODR|=(high&0x8U<<(DB7-3)); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();

	clear_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(low&0x1U<<DB4); //set
	GPIOF->ODR|=(low&0x2U<<(DB5-1)); //set
	GPIOE->ODR|=(low&0x4U<<(DB6-2)); //set
	GPIOF->ODR|=(low&0x8U<<(DB7-3)); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();
}
void place_LCD_cursor(int num){
	clear_pin(RS);
	while(num>0) {
		LCD_sendInstr(0x1U, 0x6U);
		num--;
	}
}

void switch_line(int line) {
		if(line == 2){
			LCD_sendInstr(0xc, 0);
		}else if(line == 1){
			LCD_sendInstr(0xc, 0);
			place_LCD_cursor(40);
		}			
}

//delay 6000 for about 1 sec
void delay(int time){
	while(time>=0) {
		time = time - 1;
	}
}

void intToChar(int num){
	char character;
	character = num%10 +'0';
	num = num /10;
	if(num!=0) {
		intToChar(num);
	}
	LCD_sendData(character); 
	
	
}

void doubleToLCD(double num, int sigfig) {
	int integer = num;
	intToChar(integer);
	
	LCD_sendData('.');
	
	num = num - integer;
	for(int i=0; i<sigfig && num>0; i++) {
		num = num * 10;
		integer = num;
		LCD_sendData(integer+'0');
		num = num - integer;
	}
}

void clear_pin(int pin){
	GPIOE->ODR&=~(0x1U<<pin); //clear
}

void set_pin(int pin){
	GPIOE->ODR|=(0x1U<<pin); //clear
}

void check_BF(void){
	set_pin(RW);
	clear_pin(RS);
	GPIOD->MODER &=~(3U<<DB7*2);
	set_pin(EN);
	while(GPIOD->IDR & (1<<DB7)) {
		
	}
	clear_pin(EN);
	GPIOD->MODER &=~(3U<<DB7*2);
	GPIOD->MODER |=(1U<<DB7*2);
	clear_pin(RW);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
  /* DMA1_Stream4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PG3 USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_3|USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
