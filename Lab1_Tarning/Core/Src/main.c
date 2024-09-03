/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
int is_blue_button_pressed();
void put_die_dots(uint8_t);

//sseg
void put_on_sseg(uint8_t);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
int is_blue_button_pressed()
{
	uint32_t reg_idr = GPIOC->IDR;
	uint16_t pin_b1	 = (1<<13);

	if ((reg_idr & pin_b1)== 0){
		return 1;
	}
	else {
		return 0;
	}
	HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_RESET);

}



void put_die_dots(uint8_t die_nbr){
	switch (die_nbr) {
	case 1:
		//Tänd nr1
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_SET);

		//släck alla andra
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		//Tänd nr2
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);

		//Släck andra
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		//Tänd nr3
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);

		//Släck andra
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		//Tänd nr4
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);

		//släck andra
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_RESET);

		break;
	case 5:
		//Tänd nr5
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_B_Pin, GPIO_PIN_SET);
		//släck andra
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_RESET);
		break;
	case 6:
		//Tänd nr6
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_SET);
		//släck G
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_RESET);
		break;
	default:
		//Tänd nr6
		HAL_GPIO_WritePin(DI_A_GPIO_Port, DI_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_D_GPIO_Port, DI_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_C_GPIO_Port, DI_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_B_GPIO_Port, DI_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(DI_E_GPIO_Port, DI_E_Pin, GPIO_PIN_SET);
		//släck G
		HAL_GPIO_WritePin(DI_G_GPIO_Port, DI_G_Pin, GPIO_PIN_SET);
		break;
	}
}


/* USER CODE BEGIN 0 */
const uint8_t sseg[] = {0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
const uint8_t sseg_err = 0xDC;

void put_on_sseg(uint8_t dec_nbr){
	uint8_t sseg_val;

	if ((dec_nbr >= 0) & (dec_nbr <= 9)){
		GPIOC->ODR  = sseg[dec_nbr];
	}
	else
	{
		sseg_val = sseg_err;
	}
	//GPIOC->ODR = sseg_val;

}




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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_Init();


  int sseg_die		  = 0;
  int pressed = 0;
  uint8_t die_value = 0;
  while (1)
  {

	  pressed = is_blue_button_pressed();
	  if (pressed)
	  {
		  //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		  die_value++;
		  if(die_value > 6){
			  die_value = 1;
		  }

		  sseg_die++;
		  if(sseg_die > 9){
			  sseg_die = 0;
		  }



	  }
	  else
	  {
		  put_on_sseg(sseg_die);
		  put_die_dots(die_value);
		  HAL_Delay(1);
		  //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	  }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|DI_C_Pin|DI_D_Pin|DI_G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DI_F_GPIO_Port, DI_F_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DI_E_Pin|DI_A_Pin|DI_B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin DI_C_Pin DI_D_Pin DI_G_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|DI_C_Pin|DI_D_Pin|DI_G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DI_F_Pin */
  GPIO_InitStruct.Pin = DI_F_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DI_F_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DI_E_Pin DI_A_Pin DI_B_Pin */
  GPIO_InitStruct.Pin = DI_E_Pin|DI_A_Pin|DI_B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
