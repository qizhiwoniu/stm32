#include "key.h"
#include "oled.h"
#include "stm32f1xx_hal.h"

void KEY_Init(void) {
    // ��ʼ�������Ĵ��룬��������GPIO����
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ���谴�������� GPIOB ��
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

#define KEY_DEBOUNCE_DELAY 50
uint8_t keyState[4] = {0};  // �� key.c �ж���
uint8_t lastKeyState[4] = {0};  // �� key.c �ж���
// ����������
void Key_Process(void) {
    // ��ȡ����״̬
    keyState[0] = ReadKey(KEY_R_A_Pin);  // ȷ�ϼ�
    keyState[1] = ReadKey(KEY_R_B_Pin);  // ��һ���˵���
    keyState[2] = ReadKey(KEY_R_C_Pin);  // ���ؼ�
    keyState[3] = ReadKey(KEY_R_D_Pin);  // �˳�/���½����ʼ�˵���
    
    // �������������ǰ����״̬���ϴ�״̬��һ�£������״̬
    if (keyState[0] != lastKeyState[0]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[0] == 1) {  // ���ȷ�ϼ�������
            taskIndex = taskTable[taskIndex].Enter;  // �л�����һ���˵�
        }
    }

    if (keyState[1] != lastKeyState[1]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[1] == 1) {  // �����һ����������
            taskIndex = taskTable[taskIndex].Next;  // �л�����һ���˵�
        }
    }

    if (keyState[2] != lastKeyState[2]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[2] == 1) {  // ������ؼ�������
            taskIndex = taskTable[taskIndex].Return;  // ������һ���˵�
        }
    }

    if (keyState[3] != lastKeyState[3]) {
        HAL_Delay(KEY_DEBOUNCE_DELAY);
        if (keyState[3] == 1) {  // ����˳���������
            taskIndex = 0;  // ���ص���ʼ�˵�
        }
    }

    // �����ϴεİ���״̬
    memcpy(lastKeyState, keyState, sizeof(keyState));
}// ������ȡ����
uint8_t ReadKey(uint16_t GPIO_Pin) {
    return (HAL_GPIO_ReadPin(GPIOB, GPIO_Pin) == GPIO_PIN_RESET) ? 1 : 0;  // ���谴������ʱ����͵�ƽ
}
