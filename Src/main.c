/* USER CODE BEGIN Header */
/*****************************************************************************
  �ļ�: main.c
  ����: Zhengyu https://gzwelink.taobao.com
  �汾: V1.0.0
  ʱ��: 20200401
	ƽ̨:MINI-STM32F103C8T6

*******************************************************************************/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "usb_device.h"
#include "gpio.h"
#include "oled.h"
#include "bmp.h"
#include "key.h"
#include "header.h"
void SystemClock_Config(void);
uint32_t ADC_buffer[BUFFER_SIZE]; // ����ȫ�ֱ���
int ADC_X_Value = 0, ADC_Y_Value = 0;
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
	OLED_Init();
	OLED_Clear();//����
	KEY_Init();
	taskIndex = 0;
 	if(HAL_ADCEx_Calibration_Start(&hadc1) != HAL_OK)//����У׼
  {
    Error_Handler();
  }
	HAL_ADC_Start(&hadc1);//����ADC
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_buffer,2);
	
	OLED_ShowString(0,1,"Power by");//��ʾ�ַ���
	OLED_ShowCHinese(18,5,0);//��
	OLED_ShowCHinese(36,5,1);//ֻ
	OLED_ShowCHinese(54,5,2);//��	
	OLED_ShowCHinese(72,5,3);//ţ
	HAL_Delay(3000);//�ȴ�3000ms
	OLED_Clear();
	
  while (1)
  {
		  Key_Process();  // ���� // ��鰴�������²˵�����
		  taskTable[taskIndex].Current_Operation();//ִ�к���
			HAL_Delay(100);  // ��ֹ��ť������Ƶ���л�
		//����1��		
		// �ɼ� ADC ����
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        ADC_X_Value = HAL_ADC_GetValue(&hadc1);

        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        ADC_Y_Value = HAL_ADC_GetValue(&hadc1);
		
		     // ���¹��λ��
        if (ADC_X_Value > 3000) {
            posX++;
        } else if (ADC_X_Value < 1000) {
            posX--;
        }

        if (ADC_Y_Value > 3000) {
            posY++;
        } else if (ADC_Y_Value < 1000) {
            posY--;
        }
		}
  
 
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}


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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
