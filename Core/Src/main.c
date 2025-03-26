/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "crc.h"
#include "dcmi.h"
#include "dma.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "memorymap.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BSP_SDRAM.h"
#include "BSP_RGB_LCD.h"
#include "GUI_Paint.h"
#include "image.h"
#include "debug_console.h"
#include "camera/dcmi_OV7670.h"
#include "ov7670/ov7670.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

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
  MX_FMC_Init();
  MX_USART1_UART_Init();
  MX_LTDC_Init();
  MX_DMA2D_Init();
  MX_TIM2_Init();
  MX_CRC_Init();
  MX_I2C4_Init();
  MX_DCMI_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	printf("******** LTDC Example ********\r\n");
	HAL_GPIO_WritePin(DISP_GPIO_Port, DISP_Pin, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	TIM2->CCR4 = 500;
	BSP_LCD_Init();
	HAL_Delay(50);
	BSP_LCD_Clear(0);

	//Pixel  800*480  RGB565
	Paint_NewImage(800, 480, 0, 0xffff);
	Paint_Clear(0xffff);
	Paint_DrawString_EN(10, 230, "1234567890", &Font24, 0x000f, 0xfff0);
	Paint_DrawString_EN(10, 260, "ABCDEFGHIJ", &Font24, BLUE, CYAN);
	Paint_DrawString_CN(10, 290, "΢ѩ����", &Font24CN, BLUE, CYAN);

	Paint_DrawRectangle(200, 230, 300, 330, RED, DRAW_FILL_EMPTY,
			DOT_PIXEL_2X2);
	Paint_DrawLine(200, 230, 300, 330, MAGENTA, LINE_STYLE_SOLID,
			DOT_PIXEL_2X2);
	Paint_DrawLine(300, 230, 200, 330, MAGENTA, LINE_STYLE_SOLID,
			DOT_PIXEL_2X2);
	Paint_DrawCircle(250, 280, 45, GREEN, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
	Paint_DrawImage(gImage_800X221, 0, 0, 800, 221);
	HAL_Delay(1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	DebugInit();

	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
#if 1
		DebugTask();
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		DebugTask();
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
#else
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		BSP_LCD_Clear(0xf000);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		BSP_LCD_Clear(0x0f00);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		HAL_Delay(1000);
		BSP_LCD_Clear(0x00f0);
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
		BSP_LCD_Clear(0x000f);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
		BSP_LCD_Clear(0xf00f);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
#endif
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 384;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 16;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV4;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  __HAL_RCC_PLLCLKOUT_ENABLE(RCC_PLL1_DIVQ);
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLL1QCLK, RCC_MCODIV_2);
}

/* USER CODE BEGIN 4 */
HAL_StatusTypeDef ov7670_write(uint8_t regAddr, uint8_t data);
extern uint8_t img_buffer[];

void DebugMain(uint32_t val)
{
	switch (val) {
	case 0:
	{
#if	1
		DebugPrint("\r\n OV7670_Init(&hdcmi, &hi2c_dcmi, 0, 0);");
		OV7670_Init(&hdcmi, &hi2c_dcmi, 0, 0);
		OV7670_Start();
#else
		DebugPrint("\r\n ov7670_init(&hdcmi, &hdma_dcmi, &hi2c_dcmi);");
		ov7670_init(&hdcmi, &hdma_dcmi, &hi2c_dcmi);
		ov7670_config(OV7670_MODE_QVGA_RGB565);
		uint32_t p_lcdData = 0xD0000000;
		ov7670_startCap(OV7670_CAP_CONTINUOUS, p_lcdData);
#endif
	}
		break;
	case 1:
	{
#if 1
		uint8_t temp1, temp2;
		if (ov7670_read(OV7670_PID, &temp1)==HAL_OK)
		{
			ov7670_read(OV7670_VER, &temp2);
			DebugPrint("\r\n ReadID %02X %02X", temp1, temp2);
		}
		else
		{
			DebugPrint("\r\n ReadID Error!");
		}
#else
		OV7670_IDTypeDef OV7670ID = {0};
		if (!DCMI_OV7670_ReadID(&OV7670ID))
		{
			DebugPrint("\r\n ReadID %02X %02X %02X %02X);",
					OV7670ID.Manufacturer_ID1, OV7670ID.Manufacturer_ID2,
					OV7670ID.PID, OV7670ID.Version);
		}
		else
		{
			DebugPrint("\r\n ReadID Error!");
		}
#endif
	}
		break;
	case 2:
	{
#ifdef	CAMERA_SCL_Pin
		DebugPrint("\r\n HAL_GPIO_WritePin(CAMERA_SCL_GPIO_Port, CAMERA_SCL_Pin, GPIO_PIN_RESET);");
		HAL_GPIO_WritePin(CAMERA_SCL_GPIO_Port, CAMERA_SCL_Pin, GPIO_PIN_RESET);
#else
		//HAL_StatusTypeDef ret = ov7670_write(0x12, 0x80);  // RESET
		//DebugPrint("\r\n ov7670_write(0x12, 0x80) = %08lX", ret);
		if (OV7670_isDriverBusy()) {
			DebugPrint("\r\n OV7670_isDriver is Busy");
		} else {
			DebugPrint("\r\n OV7670_isDriver is NOY Busy");
		}
#endif
	}
		break;
	case 3:
	{
#ifdef	CAMERA_SCL_Pin
		DebugPrint("\r\n HAL_GPIO_WritePin(CAMERA_SDA_GPIO_Port, CAMERA_SDA_Pin, GPIO_PIN_RESET);");
		HAL_GPIO_WritePin(CAMERA_SDA_GPIO_Port, CAMERA_SDA_Pin, GPIO_PIN_RESET);
#else
		//uint8_t ret = DCMI_SingleRandomWrite(OV7670_COM7, SCCB_REG_RESET);
		DebugPrint("\r\n Clearing camera buffer");
		uint16_t *buffer = (uint16_t *)img_buffer;
	#if 1
		for (int i = 0; i<(OV7670_WIDTH*OV7670_HEIGHT); i++)
		{
			*buffer = 0;
			buffer++;
		}
	#else
		for (int i = 0; i<480; i++)
		{
			uint16_t *line_buffer = buffer;
			buffer += 1600;
			for (int j = 0; j<640; j++) {
				line_buffer[i] = 0xFF;
				line_buffer++;
			}
		}
	#endif
#endif
	}
		break;
	case 4:
	{
#if	(defined(CAMERA_SCL_Pin)&&defined(CAMERA_SDA_Pin))
		DebugPrint("\r\n HAL_GPIO_WritePin(CAMERA_GPIO_Port, CAMERA_Pin, GPIO_PIN_SET);");
		HAL_GPIO_WritePin(CAMERA_SCL_GPIO_Port, CAMERA_SCL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CAMERA_SDA_GPIO_Port, CAMERA_SDA_Pin, GPIO_PIN_SET);
#else
		DebugPrint("\r\n Paint_DrawImage(gImage_800X221, 0, 0, 800, 221);");
		Paint_DrawImage(gImage_800X221, 0, 0, 800, 221);
#endif
	}
		break;
	case 5:
	{
		DebugPrint("\r\n Paint_DrawImage(img_buffer, 0, 0, OV7670_WIDTH, OV7670_HEIGHT);");
		Paint_DrawImage(img_buffer, (DISPLAY_WIDTH-OV7670_WIDTH)/2,
				(DISPLAY_HEIGHT-OV7670_HEIGHT)/2,
				OV7670_WIDTH, OV7670_HEIGHT);
	}
		break;
	}
}


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
