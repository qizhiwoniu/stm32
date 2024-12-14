#include "main.h"
#include "bmp.h"
#include "oled.h"
#include "oledfont.h"  
#include <string.h>
#include "header.h"
uint8_t taskIndex = 0;	//初始任务
uint8_t bluetooth_state = 0;
int posX = 0;  // 初始位置 X
int posY = 0;  // 初始位置 Y

//任务调度表
Menu_table_t taskTable[] =
{
    //菜单界面函数 -- 一级界面
    {0, 1, 0, 1, 0,Menu_Interface}, 
    //功能界面函数 -- 二级界面
    {1, 8, 2, 0, 7,Function_Interface1},
    {2, 9, 3, 0, 1,Function_Interface2},
		{3, 10, 4, 0, 2,Function_Interface3},
		{4, 11, 5, 0, 3,Function_Interface4},
	  {5, 12, 6, 0, 4,Function_Interface5},
		{6, 13, 7, 0, 5,Function_Interface6},
		{7, 14, 1, 0, 6,Function_Interface7},
	//功能设置界面函数 -- 三级界面
	{8, 8, 8, 1, 7,Function_Interface8},
	{9, 9, 9, 2, 1,Function_Interface9},
	{10, 10, 10, 3, 2,Function_Interface10},
	{11, 11, 11, 4, 3,Function_Interface11},
	{12, 12, 12, 5, 4,Function_Interface12},
	{13, 13, 13, 6, 5,Function_Interface13},
	{14, 14, 14, 7, 6,Function_Interface14},
};

void Menu_Interface(void){

	OLED_DrawBMP(0,0,128,8,image_uihome);
	
}
void Function_Interface1(void)
{
  OLED_DrawBMP(0,0,128,8,image_uisetting);

}
void Function_Interface2(void)
{
OLED_DrawBMP(0,0,128,8,image_uiplay);
	
}
void Function_Interface3(void)
{
OLED_DrawBMP(0,0,128,8,image_uijiaozhun);
	
}
void Function_Interface4(void)
{
OLED_DrawBMP(0,0,128,8,image_uimode);
	
}
void Function_Interface5(void)
{
OLED_DrawBMP(0,0,128,8,image_uibluetooth);
	
}
void Function_Interface6(void)
{
OLED_DrawBMP(0,0,128,8,image_uibuzuo);
	
}
void Function_Interface7(void)
{
OLED_DrawBMP(0,0,128,8,image_uiinfo);
	
}

void Function_Interface8(void)
{
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"setting");//显示字符串
}
void Function_Interface9(void)
{   
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"PLAY");//显示字符串
}
void Function_Interface10(void)
{   
	
	//UpdateJoystickPosition(); // 更新摇杆位置
	 // 屏幕参数定义
    //int boxX1 = 20, boxY1 = 20;           // 矩形左上角坐标
    //int boxX2 = 60, boxY2 = 60;           // 矩形右下角坐标
    //int centerX = (boxX1 + boxX2) / 2;    // 中心点 X 坐标
    //int centerY = (boxY1 + boxY2) / 2;    // 中心点 Y 坐标

    // 清屏
    OLED_Clear();

    // 绘制方框
    //OLED_DrawRectangle(boxX1, boxY1, boxX2, boxY2);

    // 绘制 “+” 字
    //OLED_DrawLine(centerX, boxY1 + 5, centerX, boxY2 - 5); // 竖线
    //OLED_DrawLine(boxX1 + 5, centerY, boxX2 - 5, centerY); // 横线

	 

   

        // 限制光标范围
        if (posX < 0) posX = 0;
        if (posX > 127) posX = 127; // 假设 OLED 宽度为128
        if (posY < 0) posY = 0;
        if (posY > 63) posY = 63;   // 假设 OLED 高度为64

	
	OLED_GotoXY(posX, posY);	
	OLED_ShowString(posX, posY, "+");
	OLED_UpdateScreen();
        //DisplayScreen();          // 显示更新
        HAL_Delay(100);           // 避免频繁刷新

}
void Function_Interface11(void)
{   
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"mode");//显示字符串
}
void Function_Interface12(void)
{   
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"bluetooth");//显示字符串
	 // 根据蓝牙状态显示开或关
    if (bluetooth_state)
    {
        OLED_ShowString(0, 2, "Status: ON"); // 蓝牙已开启
    }
    else
    {
        OLED_ShowString(0, 2, "Status: OFF"); // 蓝牙已关闭
    }
}
void Function_Interface13(void)
{   
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"buzuo");//显示字符串
}
void Function_Interface14(void)
{   
	OLED_Clear();//清屏
	OLED_ShowString(0,0,"v1.0");//显示字符串
  OLED_ShowCHinese(25,3,0);//七
	OLED_ShowCHinese(50,3,1);//只
	OLED_ShowCHinese(75,3,2);//蜗	
	OLED_ShowCHinese(100,3,3);//牛
	OLED_ShowString(25,5,"2024/12/05");//显示字符串
}

// 蓝牙状态切换函数
void Toggle_Bluetooth(void)
{
    bluetooth_state = !bluetooth_state; // 切换蓝牙状态
}

//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==12)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=6;
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
void OLED_GotoXY(u8 x,u8 y){}
void OLED_UpdateScreen(void){}
void OLED_DrawRectangle(u8 x1, u8 y1, u8 x2, u8 y2) {
    // 使用直线绘制函数来画矩形的四条边
    OLED_DrawLine(x1, y1, x2, y1); // 上边
    OLED_DrawLine(x2, y1, x2, y2); // 右边
    OLED_DrawLine(x2, y2, x1, y2); // 下边
    OLED_DrawLine(x1, y2, x1, y1); // 左边
}	
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2) {
    // 实现代码：绘制一条从 (x1, y1) 到 (x2, y2) 的线
}
// 定义 UpdateJoystickPosition 函数
void UpdateJoystickPosition(void) {
    // 根据摇杆的 ADC 值更新坐标
    if (ADC_buffer[0] > 3000) { // 右移
        posX += CHAR_WIDTH;
        if (posX > BOX_X + BOX_WIDTH - CHAR_WIDTH) posX = BOX_X + BOX_WIDTH - CHAR_WIDTH;
    } else if (ADC_buffer[0] < 1000) { // 左移
        posX -= CHAR_WIDTH;
        if (posX < BOX_X) posX = BOX_X;
    }

    if (ADC_buffer[1] > 3000) { // 上移
        posY -= CHAR_HEIGHT;
        if (posY < BOX_Y) posY = BOX_Y;
    } else if (ADC_buffer[1] < 1000) { // 下移
        posY += CHAR_HEIGHT;
        if (posY > BOX_Y + BOX_HEIGHT - CHAR_HEIGHT) posY = BOX_Y + BOX_HEIGHT - CHAR_HEIGHT;
    }
}

// 定义 DisplayScreen 函数
void DisplayScreen(void) {
    OLED_Clear(); // 清屏

    // 绘制方框
    OLED_DrawRectangle(BOX_X, BOX_Y, BOX_X + BOX_WIDTH, BOX_Y + BOX_HEIGHT);

    // 绘制字符 '+'
    OLED_GotoXY(posX, posY);
    OLED_ShowString(posX, posY, "+");

    OLED_UpdateScreen(); // 更新屏幕
	  HAL_Delay(100); 
}


//初始化SSD1306					    
void OLED_Init(void)
{ 	

  GPIO_InitTypeDef GPIO_InitStruct = {0};
 __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;//配置管脚为输出
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0xf0,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  


























