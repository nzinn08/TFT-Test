/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hspi.h"
#include "gfx.h"
#include "text-box.h"
#include "quarter-sorter-specific.h"
#include "selection-encoder.h"
#include <stdio.h>
#include "sw-debounce.h"
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
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

SELECTION_ENCODER* encoderPtr = nullptr;

SW_DEBOUNCE* okButtonPtr = nullptr;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  TFT_GFX tftDisplay{hspi2.Instance};
  const uint16_t backgroundColor = ILI9341_BLACK;
  const uint16_t fontColor = ILI9341_DARK_ORANGE;
  const uint16_t lineColor = ILI9341_DARK_ORANGE;
  const uint16_t lineThickness = 5;
  const uint8_t chosenStatesFontSize = 2;
  const uint8_t stateSelectorFontSize = 3;
  tftDisplay.setRotation(0);
  //Set background to correct color and add outline
  GUI_API::drawSelectionLines(tftDisplay, backgroundColor, fontColor, lineColor, lineThickness);
  //Create and set all the text boxes
  TFT_TEXT_BOX instructionBox{&tftDisplay,backgroundColor,lineThickness + 8, lineThickness + 8, (int16_t)(tftDisplay.width() - lineThickness - 8), false};
  uint16_t bottomInstructionBox = instructionBox.write("*Hold OK button for 3 seconds to confirm selection.", fontColor, 1);
  TFT_TEXT_BOX mainTitle{&tftDisplay,backgroundColor,lineThickness + 8, (uint16_t)(bottomInstructionBox + 10),(int16_t)(tftDisplay.width() - lineThickness - 8), false};
  uint16_t bottomMainTitle = mainTitle.write("State Selection: ", fontColor, 2);
  TFT_TEXT_BOX stateSelector{&tftDisplay, backgroundColor, lineThickness, (uint16_t)(bottomMainTitle + 25),(int16_t)(tftDisplay.width() - lineThickness), true};
  //Generate the chosenStates text boxes
  CHOSEN_STATE_TEXT_BOX chosenStates[NUM_BOXES];
  uint8_t statesSelected = 0;
  for(uint8_t i = 0; i < NUM_BOXES; i++)
  {
	  uint16_t yPos = tftDisplay.height()/2.0f + (float)(2*i+1)*tftDisplay.height()/(2.0f* NUM_BOXES * 2.0f) - (chosenStatesFontSize * 8.0f)/2;
	  chosenStates[i] = CHOSEN_STATE_TEXT_BOX{(uint8_t)(i+1), fontColor, chosenStatesFontSize, TFT_TEXT_BOX{&tftDisplay, backgroundColor, lineThickness + 8, yPos,(int16_t)(tftDisplay.width() - lineThickness - 8), false}};
  }
  stateSelector.write(stateNames[0], fontColor, stateSelectorFontSize);
  //Initialize debouncer for buttons
  SW_DEBOUNCE okButton{ENC_OK_GPIO_Port, ENC_OK_Pin, 2, 8, htim6.Instance};
  okButtonPtr = &okButton;
  //Start timer after initializing all buttons
  htim6.Instance->CR1 |= TIM_CR1_CEN;
  //Initialize Rotary Encoder
  SELECTION_ENCODER stateEncoder{1, &stateSelector, fontColor, stateSelectorFontSize, stateNames, NUM_NAMES, chosenStates, NUM_BOXES};
  encoderPtr = &stateEncoder;
  //Now enable interrupts for the rotary encoder and debouncer
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  SWITCH_STATE currButtonState = okButton.getCurrentState();
	  if(currButtonState == SWITCH_STATE::SHORT_PRESS)
	  {
		  GUI_API::printCurrentState(chosenStates, statesSelected, encoderPtr);
	  }else if(currButtonState == SWITCH_STATE::THREE_SECOND_PRESS)
	  {
		  //This should be where we go to the screen that simply displays that sorting is in progress.
		  /*GUI_API::resetSelectionGUI(tftDisplay, instructionBox, mainTitle, stateSelector, backgroundColor, fontColor, lineColor,
				  lineThickness, stateSelectorFontSize, statesSelected);*/
		//TODO: Need to disable encoder and ok button in here
		GUI_API::displayInProgress(tftDisplay, instructionBox, lineThickness, lineColor, backgroundColor, fontColor);
		TFT_TEXT_BOX confirmQuit{&tftDisplay, backgroundColor, lineThickness + 8, (uint16_t)(3*tftDisplay.height()/5.0f),(int16_t)(tftDisplay.width() - lineThickness - 8), true};
		uint16_t bottomConfirmQuit = confirmQuit.write("*Are you sure you want to quit?*", fontColor, 2);
		TFT_TEXT_BOX confirmQuitInstructions{&tftDisplay, backgroundColor, lineThickness + 8, (uint16_t)(bottomConfirmQuit + 10),(int16_t)(tftDisplay.width() - lineThickness - 8), true};
		confirmQuitInstructions.write("Hold cancel for 3 seconds to confirm quit, tap to cancel.", fontColor, 1);
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */
  //Send 1 random byte to reset the sck
  uint8_t temp = 0;
  HAL_SPI_Transmit(&hspi2, &temp, sizeof(temp), HAL_MAX_DELAY);
  resetTftBoard();
  pullCSLow();
  ili9341_hspi_init(hspi2.Instance);
  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */
  //Set a period of 2ms
  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 240-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 400-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */
  //Clear status reg
  htim6.Instance->SR &= TIM_SR_UIF;
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 0);
  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TFT_D_C_GPIO_Port, TFT_D_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, TFT_RST_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_D_C_Pin SPI2_NSS_Pin */
  GPIO_InitStruct.Pin = TFT_D_C_Pin|SPI2_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : TFT_RST_Pin LD2_Pin */
  GPIO_InitStruct.Pin = TFT_RST_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_B_Pin */
  GPIO_InitStruct.Pin = ENC_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ENC_B_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_A_Pin */
  GPIO_InitStruct.Pin = ENC_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ENC_A_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ENC_OK_Pin */
  GPIO_InitStruct.Pin = ENC_OK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ENC_OK_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
