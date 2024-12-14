#ifndef HEADER_H
#define HEADER_H
#include "oled.h"
#include <stdint.h>

#define BUFFER_SIZE 2
extern uint32_t ADC_buffer[BUFFER_SIZE]; // ����ȫ�ֱ���
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define CHAR_WIDTH 6   // �ַ����
#define CHAR_HEIGHT 8  // �ַ��߶�

// ���巽�������ͳߴ�
#define BOX_X 10
#define BOX_Y 10
#define BOX_WIDTH 50
#define BOX_HEIGHT 30
// ȫ�ֱ�������
extern int posX;
extern int posY;

void UpdateJoystickPosition(void);
void DisplayScreen(void);
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2);
#endif // HEADER_H