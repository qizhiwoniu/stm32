#include "key.h"
#include "oled.h"
#include "stm32f1xx_hal.h"

void KEY_Init(void) {
    // 初始化按键的代码，例如配置GPIO引脚
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 假设按键连接在 GPIOB 上
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

#define KEY_DEBOUNCE_DELAY 50
uint8_t keyState[4] = {0};  // 在 key.c 中定义
uint8_t lastKeyState[4] = {0};  // 在 key.c 中定义
// 按键处理函数
void Key_Process(void) {
    // 读取按键状态
    keyState[0] = ReadKey(KEY_R_A_Pin);  // 确认键
    keyState[1] = ReadKey(KEY_R_B_Pin);  // 下一个菜单键
    keyState[2] = ReadKey(KEY_R_C_Pin);  // 返回键
    keyState[3] = ReadKey(KEY_R_D_Pin);  // 退出/重新进入初始菜单键
    
    // 防抖处理：如果当前按键状态与上次状态不一致，则更新状态
    if (keyState[0] != lastKeyState[0]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[0] == 1) {  // 如果确认键被按下
            taskIndex = taskTable[taskIndex].Enter;  // 切换到下一个菜单
        }
    }

    if (keyState[1] != lastKeyState[1]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[1] == 1) {  // 如果下一个键被按下
            taskIndex = taskTable[taskIndex].Next;  // 切换到下一个菜单
        }
    }

    if (keyState[2] != lastKeyState[2]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[2] == 1) {  // 如果返回键被按下
            taskIndex = taskTable[taskIndex].Return;  // 返回上一级菜单
        }
    }

    if (keyState[3] != lastKeyState[3]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[3] == 1) {  // 如果退出键被按下
            taskIndex = 0;  // 返回到初始菜单
        }
    }

    // 更新上次的按键状态
    memcpy(lastKeyState, keyState, sizeof(keyState));
}// 按键读取函数
uint8_t ReadKey(uint16_t GPIO_Pin) {
    return (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_RESET) ? 1 : 0;  // 假设按键按下时输出低电平
}
