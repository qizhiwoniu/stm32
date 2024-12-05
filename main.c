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
#include "stm32f1xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "oled.h"
#include "bmp.h"
#include "rtc.h"
#include "key.h"
void SystemClock_Config(void);
/* �����Ƴ�ʼ��*/
void HAL_delay_us(uint32_t us)
{
    uint32_t Delay = us * 32/4;
    do
    {
        __NOP();
    }
    while (Delay --);
}

uint8_t aShowTime[16] = "hh:ms:ss";//����ʱ����
uint8_t aShowDate[16] = "dd-mm-yyyy";//����������
//��ȡ���ڣ�ʱ�䣬
static void RTC_CalendarShow(uint8_t *showtime, uint8_t *showdate)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);
//  /* Display time Format : hh:mm:ss */
  //sprintf((char *)showtime, "%2d:%2d:%2d", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
//  /* Display date Format : mm.dd.yy */
  //sprintf((char *)showdate, "%2d.%2d.%2d", 2000 + sdatestructureget.Year,sdatestructureget.Month, sdatestructureget.Date);
}
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
  SystemClock_Config();//8M�ⲿ����72M��Ƶ

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	MX_RTC_Init();                //RTC��ʼ��
  /* USER CODE BEGIN 2 */
		KEY_Init();
		OLED_Init();//OLED��ʼ��  
		OLED_Clear();//����
	  taskIndex = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  //��ʾ����
	OLED_ShowString(0,1,"Power by");//��ʾ�ַ���
	OLED_ShowCHinese(18,5,0);//��
	OLED_ShowCHinese(36,5,1);//ֻ
	OLED_ShowCHinese(54,5,2);//��	
	OLED_ShowCHinese(72,5,3);//ţ
	HAL_Delay(3000);//�ȴ�3000ms
	{//////////////��ʾ����Ч��//////////////////
	OLED_DrawBMP(0,0,128,8,BMP_load1);  //ͼƬ��ʾ��ת
	HAL_Delay(50);//�ȴ�50ms
	OLED_DrawBMP(0,0,128,8,BMP_load2);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load3);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load4);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load5);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load6);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load7);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load8);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load9);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load10);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load11);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load12);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load13);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load14);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load1);  //ͼƬ��ʾ��ת
	HAL_Delay(50);//�ȴ�50ms
	OLED_DrawBMP(0,0,128,8,BMP_load2);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load3);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load4);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load5);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load6);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load7);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load8);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load9);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load10);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load11);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load12);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load13);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	OLED_DrawBMP(0,0,128,8,BMP_load14);  //ͼƬ��ʾ��ת
	HAL_Delay(50);
	}
	//HAL_Delay(2000);
	OLED_Clear();//����
	//OLED_DrawBMP(0,0,128,8,BMP_MENU);  //ͼƬ��ʾ�˵���Ļ
	//OLED_DrawBMP(0,0,128,8,image_uihome);
	 while (1)
  {
			
		  //RTC_CalendarShow(aShowTime, aShowDate);//��ȡʱ�䣬���ڱ��浽����
			//OLED_ShowString(0,0,aShowTime);//��ʾ�ַ���
			//OLED_ShowString(32,2,aShowDate);//��ʾ�ַ���
		  Key_Process();  // ���� // ��鰴�������²˵�����
		  taskTable[taskIndex].Current_Operation();//ִ�к���
			HAL_Delay(100);  // ��ֹ��ť������Ƶ���л�
			
	}
	
	/*
	int i = 1;
  while (1)
  {
		
			while( i <1300 )
			{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			HAL_delay_us(i);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			HAL_delay_us(1300-i);
			i++;
			}
			while( i > 1 )
			{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			HAL_delay_us(i);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			HAL_delay_us(1300-i);
			i--;
			}
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);//PC13���ŷ�ת���
		//HAL_Delay(100);//�ȴ�100ms
		
		}
*/
	
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

