#include "pwm.h"
#include "timer.h" 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"  
#include "usart2.h"  
#include "ov7725.h" 
#include "sram.h"
#include "motion.h"
#include "pid.h"


//90帧
extern u8 ov_sta;
extern u8 function;
extern u16 frame;
extern u16 ball_i;
extern u16 ball_j;
extern u8 abc;
extern u8 select_zone;
void camera_refresh(void)
{
	u16 i;
	u16 j;
	u16 r;
	u16 g;
	u16 b;
	u16 gray;
 	u16 color;	 
	u16 j_max=0;
	u16 i_max=0;
	u16 j_min=400;
	u16 i_min=400;
  u16 ball_i_temp;
	u16 ball_j_temp;
	
	//问题1：有光晕存在，采用滤波算法解决？
	//问题2：
	
	if(ov_sta)//有帧中断更新？
	{
		
		//初始化LCD GRAM
		LCD_Scan_Dir(U2D_L2R);		//从上到下,从左到右  应与传输的数据方向保持一致不可更改
		LCD_WriteRAM_Prepare();     //开始写入GRAM	
		
		OV7725_RRST=0;				//开始复位读指针 
		OV7725_RCK_L;
		OV7725_RCK_H;
		OV7725_RCK_L;
		OV7725_RRST=1;				//复位读指针结束 
		OV7725_RCK_H;
	
		
	/*************图像处理***************/
	for(i=0;i<240;i++)//列数
		{
		for(j=0;j<320;j++)  //行数  只传送颜色的值即可
		{
			OV7725_RCK_L;
			color=OV7725_DATA;	//读数据
			OV7725_RCK_H; 
			color<<=8; 
			OV7725_RCK_L;
			color|=OV7725_DATA;	//读数据
			OV7725_RCK_H;
			r = color&0XF800>>11;
			g = color&0X07E0>>5;
			b = color&0X001F;

		   gray = (r + g + b) ;
		
			if(gray<20)//gray越小越黑
			{
				color=0x0000;
				if((j<42)||(j>250)||(i>230)||(i<24))
				{
				color=0xffff;
				}
			}
			else
			{
			color=0xffff;
			}
					
	   /////////计算最大与最小位置////////////
			if(color==0x0000)
			{
       if(j_max<j)
			 {
			 j_max=j;
			 }
			 if(j<j_min)
			 {
			 j_min=j;
			 }
			 if(i_max<i)
			 {
			 i_max=i;
			 }
			 if(i<i_min)
			 {
			 i_min=i;
			 }
			}
		///////////////////	
			
		LCD->LCD_RAM = color; //放入LCD显示
		}
	}
		if(j_max-j_min<25)
		{
			ball_j_temp=(j_max+j_min)/2;
			ball_i_temp=(i_max+i_min)/2;
			if((ball_j_temp==ball_i_temp)&(ball_i_temp==200))
			{}
			else
			{
				ball_j=ball_j_temp;
				ball_i=ball_i_temp;
				//printf("ball_j: %d ball_j: %d \r\n",ball_j,ball_i);
				
			}
		}

/*************图像处理***************/	

 		ov_sta=0;					//清零帧中断标
		LCD_Scan_Dir(DFT_SCAN_DIR);	//恢复默认扫描方向
		//LED1=!LED1;
	} 
}


int main(void)
{ 
	u8 key_value;
	u8 flag_first=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED
 	LCD_Init();					//LCD初始化
 	KEY_Init();					//按键初始化
	pid1_init();
	pid2_init();
	//FSMC_SRAM_Init();
 	POINT_COLOR=RED;//设置字体为红色 
	//LCD_ShowString(30,70,200,16,16,"OV7725 TEST");	
  setzone_init();
	TIM14_PWM_Init(20000-1,84-1);	
	TIM13_PWM_Init(20000-1,84-1);
	
	  j_in(0);
		i_in(0);
	
	  delay_ms(1000);
		
	while(OV7725_Init())//初始化OV7670
	{
		LCD_ShowString(30,130,240,16,16,"7725 ERR");
		delay_ms(200);
		LCD_Fill(30,130,239,170,WHITE);
		delay_ms(200);
		LED0=!LED0;  
	}
	
	LCD_ShowString(30,130,200,16,16,"7725 OK");  		
	delay_ms(1500);	 	   
	EXTI8_Init();						//使能定时器捕获
	OV7725_Window_Set(320,240 ,0);	//设置窗口 有时候0不行？？
  OV7725_CS=0;					
	LCD_Clear(BLACK);	 

	
 	while(1)
	{	
		camera_refresh();//更新显示
		if(flag_first<2)
		{
			flag_first++;
		  TIM3_Int_Init(21000-1,168-1);
    }
	 key_value = KEY_Scan(0);
 
	//主界面
	if(function==0)
	{
//		
	//LCD_ShowString(30,130,200,24,16,"Function Chose");

	if(key_value==1)
	{	
		LCD_Clear(BLUE);
		function=1;
	}

	else if(key_value==2)
	{	LCD_Clear(BLUE);
	function=2;
	}
	
  else if(key_value==3)
  {	LCD_Clear(BLUE);
		function=3;
	}
	
  else if(key_value==4)
  {	LCD_Clear(BLUE);
		function=4;
	}
	
  else if(key_value==5)
  {	LCD_Clear(BLUE);
		function=5;
	}	
	
	else if(key_value==6)
  {	LCD_Clear(BLUE);
		function=6;
	}
	
	  else if(key_value==7)
  {	LCD_Clear(BLUE);
		function=7;
	}	

	
	}
//	
//	
//	
	//功能1
	if(function==1)
	{
	LCD_ShowString(30,130,200,16,16," function 1");

	if(key_value==50)
	{
		LCD_Clear(BLUE);
		function=0;
	}
	
	}
//	
//	
//	
//	//功能2
	if(function==2)
	{	
	LCD_ShowString(30,130,200,16,16,"function 2");
	if(key_value==50)
	{
		LCD_Clear(BLUE);
		function=0;
	}
	}
	
//	
//	
//	
	//功能3
	if(function==3)
	{		
		LCD_ShowString(30,130,200,16,16,"function 3");
	if(key_value==50)
	{
		LCD_Clear(BLUE);
		function=0;
	}
	}
//	
//	
//	
//	//功能4
	if(function==4)
	{
		LCD_ShowString(30,130,200,16,16,"function 4");
	if(key_value==50)
	{
		LCD_Clear(BLUE);
		function=0;
	}
	}
//	
//	
//	
//	
	//功能5
	if(function==5)
	{
		LCD_ShowString(30,130,200,16,16,"function 5");
	if(key_value==50)
	{ 
  	LCD_Clear(BLUE);
		function=0;
	}
	}
	
	
	if(function==6)
	{
		LCD_Clear(BLUE);
		LCD_ShowString(30,190,200,16,16,"function 6");
		LCD_ShowxNum(30,150,abc,16,16,0);
	if(key_value==50)
	{ 
		
		function=0;
	}
	
	else if(key_value==10)
	{
   abc=abc+1;
	}
	else if(key_value==1)
	{ 
	  select_zone=1; }
		else if(key_value==2)
	{ select_zone=2; }
		else if(key_value==3)
	{ select_zone=3; }
		else if(key_value==4)
	{ select_zone=4; }
		else if(key_value==5)
	{ select_zone=5; }
		else if(key_value==6)
	{ select_zone=6; }
		else if(key_value==7)
	{ select_zone=7; }
		else if(key_value==8)
	{ select_zone=8; }
		else if(key_value==9)
	{ select_zone=9; }
	
	}
	
	
if(function==7)
	{
		if(key_value==50)
	{ 
		
		function=0;
	}
	
	}

	}	   

}
