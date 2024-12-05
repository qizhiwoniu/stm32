#ifndef __KEY_H
#define __KEY_H
#include "stm32f1xx_hal.h"
#include "gpio.h"

/*************板载LED控制*************/

#define Board_LED_ON HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_OFF HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1)
#define Board_LED_Toggle HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)

/*************按键消抖*************/

// 按键为1时触发
uint8_t trigger_gpio(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
// 按键为0时触发
uint8_t trigger_gpio_up(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/*************右侧按键的读取*************/

#define KEY_R_A_GPIO_Port GPIOB
#define KEY_R_A_Pin GPIO_PIN_4
#define KEY_R_B_GPIO_Port GPIOB
#define KEY_R_B_Pin GPIO_PIN_3
#define KEY_R_C_GPIO_Port GPIOB
#define KEY_R_C_Pin GPIO_PIN_1
#define KEY_R_D_GPIO_Port GPIOB
#define KEY_R_D_Pin GPIO_PIN_0

void KEY_Init(void);
extern uint8_t keyState[4];  // 声明全局变量
extern uint8_t lastKeyState[4];  // 声明全局变量
extern uint8_t ReadKey(uint16_t GPIO_Pin);  // 声明
#endif
