#include "stm32f4xx.h" 
#include "key.h"
#include "sys.h" 
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
	
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//使能PORTA,PORTE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_14|GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
//	
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	
 	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	
}


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

u8 KEY_Scan(u8 mode)
{	 
	
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0||KEY7==0||KEY8==0||KEY9==0||KEY10==0))
	{
		delay_ms(5);//去抖动 
		key_up=0;
	 //if(KEY7==0)return KEY7_PRES;
		//else if(KEY8==0)return KEY8_PRES;
    if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
		else if(KEY5==0)return KEY5_PRES;
		else if(KEY6==0)return KEY6_PRES;
		else if(KEY7==0)return KEY7_PRES;
		else if(KEY8==0)return KEY8_PRES;
		else if(KEY9==0)return KEY9_PRES;
		else if(KEY10==0)return KEY10_PRES;
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1&&KEY7==1&&KEY8==1&&KEY0==1&&KEY9==1&&KEY10==1)key_up=1; 	      
 	return 0;// 无按键按下
	
}













