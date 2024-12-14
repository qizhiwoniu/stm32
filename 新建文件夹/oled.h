
#ifndef __OLED_H
#define __OLED_H			  	 
#include "main.h"  
#include <string.h>
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    




//-----------------OLED�˿ڶ���----------------  					   


#define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)//CLK 
#define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)//DIN
#define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)


#define OLED_DC_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#define KEY_R_A_GPIO_Port GPIOB
#define KEY_R_A_Pin GPIO_PIN_4
#define KEY_R_B_GPIO_Port GPIOB
#define KEY_R_B_Pin GPIO_PIN_3
#define KEY_R_C_GPIO_Port GPIOB
#define KEY_R_C_Pin GPIO_PIN_1
#define KEY_R_D_GPIO_Port GPIOB
#define KEY_R_D_Pin GPIO_PIN_0
//---------------------------------------------
typedef struct
{
	uint8_t CurrentNum;	//��ǰ�������:ҳ��
	uint8_t Enter;		//ȷ�ϼ�
	uint8_t Next;		//��һ��
	uint8_t Return;		//���ؼ�
	void (*Current_Operation)(void);//��ǰ����(����ָ��)
}Menu_table_t;

extern uint8_t taskIndex;
extern Menu_table_t taskTable[];

void Menu_Interface(void);
void Function_Interface1(void);
void Function_Interface2(void);
void Function_Interface3(void);
void Function_Interface4(void);
void Function_Interface5(void);
void Function_Interface6(void);
//---------------------------------------------
//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);


#endif  
	 



