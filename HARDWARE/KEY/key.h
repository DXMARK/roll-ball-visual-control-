#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define KEY1  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)//��ȡ����1
#define KEY3  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3)//��ȡ����1
#define KEY4  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)//��ȡ����1
#define KEY5  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)//��ȡ����1
#define KEY6  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)//��ȡ����1
#define KEY7  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_14)//��ȡ����1
#define KEY8  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_15)//��ȡ����1
#define KEY9  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����1
#define KEY10  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����1


#define KEY1_PRES 1	//KEY0����
#define KEY2_PRES	2	//KEY1����
#define KEY3_PRES	3	//KEY2����
#define KEY4_PRES	4//KEY1����
#define KEY5_PRES	5	//KEY2����
#define KEY6_PRES	6	//KEY2����
#define KEY7_PRES	7	//KEY2����
#define KEY8_PRES	8	//KEY2����
#define KEY0_PRES	50	//KEY2����
#define KEY9_PRES	9	//KEY2����
#define KEY10_PRES	10	//KEY2����


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
