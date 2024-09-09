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

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	enum event {
		ev_none,
		ev_button_push,
		ev_state_timeout
	};

	enum state {
		s_init,
		s_1,
		s_2,
		s_3,
		s_4,
		s_5,
		s_6,
		s_7,
		s_R_R,
		s_R_G,
		s_RY_R,
		s_G_R,
		s_Y_R
	};

void set_traffic_lights(enum state s){

		switch(s) {

		case s_init:

			//Car Lights on
			HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_SET); //Red
			HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_SET); //Yellow
			HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_SET); //Green

			//Passer Lights on
			HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_SET); //Green
			HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_SET); //Red

		break;

		case s_R_R:

			//Car Red
			HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_SET);
			//Passer Red
			HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_SET);

			//Rest reset (turn off)
			HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_RESET);

		break;

		case s_R_G:
				// Car red, passer green
		        HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_SET);

		        //Reset rest
		        HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_RESET);
		        break;

		    case s_RY_R:
		    	//Car red and yellow, passer red
		        HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_SET);
		        //Reset rest
		        HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_RESET);
		        break;

		    case s_G_R:
		    	//Car green, passer red
		        HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_SET);
		        // Reset rest
		        HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_RESET);
		        break;

		    case s_Y_R:
		    	//Car yellow, Passer Red
		        HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_SET);
		        //Reset rest
		        HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);
		        HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_RESET);
		        break;
		    default:
		    	//All turned off
		    	HAL_GPIO_WritePin(CAR_A_GPIO_Port, CAR_A_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(CAR_B_GPIO_Port, CAR_B_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(P_D_GPIO_Port, P_D_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(P_E_GPIO_Port, P_E_Pin, GPIO_PIN_RESET);
		    }

		}

void push_button_light_on(void){

	if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 0) {
		HAL_GPIO_WritePin(B1_Lg_GPIO_Port, B1_Lg_Pin, GPIO_PIN_SET);
	};

}

void push_button_light_off(void){

	if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 1) {
		HAL_GPIO_WritePin(B1_Lg_GPIO_Port, B1_Lg_Pin, GPIO_PIN_RESET);
	};
}

int is_blue_button_pressed(void){
	if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == 0) {
		return 1;
	}
	return 0;
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
enum state st_lg	= s_init;
enum event ev 		= ev_none;
enum state st_sw 	= s_1;
int curr_press		= 0;
int last_press		= 0;

unit32_t ticks_left_in_state = 0;
uint32_t curr_tick = 0;
unit32_t last_tick = 0;





  while (1)
  {


	  curr_press = is_button_pressed();

	  if (curr_press && !last_press) {
		  ev = ev_button_push;
	  }
	  last_press = curr_press;

	  //Tick handler
	  curr_tick = HAL_GetTick();
	  if (curr_tick != last_tick) {

		if (ticks_left_in_state > 0) {
			ticks_left_in_state--;
		}//end if 2
		if (ticks_left_in_state == 0 && ){
			ev = ev_state_timeout;
		}//end if 3
		last_tick = curr_tick;

	  }//end if 1

	  switch(st_sw){

	  case s_1:


		  if (ev = ev_none) {
			  st_lg = s_R_R;
			  st_sw = s_2;
			  ticks_left_in_state = 3000;
			  set_traffic_lights(st_lg); //den kmr köra R_R nu
		  }

		  break;

	  case s_2:
		  if (ev = ev_state_timeout) {
			  st_lg = s_G_R;
			  st_sw = s_3;
			  ticks_left_in_state = 3000;
			  set_traffic_lights(st_lg); //s_G_R
		  }

		  break;

	  case s_3:
		  if (ev = ev_button_push) {
			  st_lg = s_Y_R;
			  st_sw = s_4;
			  ticks_left_in_state = 3000;
			  set_traffic_lights(st_lg);
		  }else
		  {
			  st_sw = s_2;
		  }























    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  HAL_GPIO_WritePin(GPIOC, CAR_A_Pin|CAR_B_Pin|B1_Lg_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, P_E_Pin|P_D_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CAR_C_GPIO_Port, CAR_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CAR_A_Pin CAR_B_Pin B1_Lg_Pin */
  GPIO_InitStruct.Pin = CAR_A_Pin|CAR_B_Pin|B1_Lg_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : P_E_Pin P_D_Pin LD2_Pin */
  GPIO_InitStruct.Pin = P_E_Pin|P_D_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : CAR_C_Pin */
  GPIO_InitStruct.Pin = CAR_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CAR_C_GPIO_Port, &GPIO_InitStruct);

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
