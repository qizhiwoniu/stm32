#ifndef HEADER_H
#define HEADER_H
#include "oled.h"
#include <stdint.h>

#define BUFFER_SIZE 2
extern uint32_t ADC_buffer[BUFFER_SIZE]; // 声明全局变量
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define CHAR_WIDTH 6   // 字符宽度
#define CHAR_HEIGHT 8  // 字符高度

// 定义方框的坐标和尺寸
#define BOX_X 10
#define BOX_Y 10
#define BOX_WIDTH 50
#define BOX_HEIGHT 30
// 全局变量声明
extern int posX;
extern int posY;

void UpdateJoystickPosition(void);
void DisplayScreen(void);
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2);
#endif // HEADER_H