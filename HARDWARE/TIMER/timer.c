#include "timer.h"
#include "led.h"
#include "usart.h"
#include "motion.h"
#include "pid.h"
#include "math.h"

////////////////////////////////////////////////////////////////////////////////// 	 

//extern u8 ov_frame;
//extern volatile u16 jpeg_data_len;



//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


//tim14��Ӧj��tim13��Ӧi
extern u16 frame;
u8 set_zone_i[9];
u8 set_zone_j[9];


void setzone_init(void)
{
   *set_zone_i=52;
   *set_zone_j=80;
	
	 *(set_zone_i+1)=115;
   *(set_zone_j+1)=79;
	
	 *(set_zone_i+2)=191;
   *(set_zone_j+2)=81;
	
	 *(set_zone_i+3)=54;
   *(set_zone_j+3)=146;
	
	 *(set_zone_i+4)=123;
   *(set_zone_j+4)=146;
	
	 *(set_zone_i+5)=190;
   *(set_zone_j+5)=147;
	
	 *(set_zone_i+6)=52;
   *(set_zone_j+6)=219;
	
	*(set_zone_i+7)=121;
  *(set_zone_j+7)=220;
 
 *(set_zone_i+8)=191;
 *(set_zone_j+8)=222;
	
}


u8 set_zone9_i=184,set_zone9_j=222;
u8 set_zone8_i=121,set_zone8_j=220;
u8 set_zone7_i=50,set_zone7_j=212;
u8 set_zone6_i=195,set_zone6_j=153;
u8 set_zone5_i=125,set_zone5_j=149;
u8 set_zone4_i=57,set_zone4_j=141;
u8 set_zone3_i=199,set_zone3_j=85;
u8 set_zone2_i=131,set_zone2_j=78;
u8 set_zone1_i=61,set_zone1_j=71;
extern u8 ov_sta;
u8 function=0;

u16 ball_i=0;
u16 ball_j=0;

extern u8 two_finish;

//����5  
u8 enter2_suc=0;
u8 enter6_suc=0;

//����6
u8 abc=0;
u8 set_zonef_i,set_zonef_j;
u8 set_zones_i,set_zones_j;
u8 set_zonet_i,set_zonet_j;
u8 select_zone=0;


//7
u8 fun7_count=3;
double theta=0.0;
u8 all_success=0;
u8 en_success=0;
u16 fun_7_temp=0;

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
  
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		printf("bi:%d  bj: %d ",ball_i,ball_j);
		if(function==0)
		{
      i_in(0);
		  enter2_suc=0;
      enter6_suc=0;
			abc=0;
			j_in(0);
			 fun_7_temp=0;
		}
		
		/*����1������2*/
		else if(function==1)
		{
    set_point_func1(set_zone2_i,set_zone2_j,ball_i,ball_j);
		}
		
		/*����2����1����5*/
		else if(function==2)
		{
				pid1_set_f1(16,0,140);
        pid2_set_f1(15,0,140);
        set_point(set_zone5_i,set_zone5_j,ball_i,ball_j,0,0);
		}
		
	  /*����3����1����4ͣ�����룬�ٽ���5*/
		else if(function==3)
		{
			
			if(two_finish==0)
			{
			pid1_set_f1(15,0,140);
	    pid2_set_f1(15,0,140);
			set_point_function2_4(set_zone4_i,set_zone4_j,ball_i,ball_j,0,0);
			}
			
			else if(two_finish==1)
	   	{
			pid1_set_f1(16,0,140);
      pid2_set_f1(15,0,140);
			set_point(set_zone5_i,set_zone5_j,ball_i,ball_j,0,0);
			}
			
			}
		
		
		/*����4����1����9*/
		else if(function==4)
		{
			if(((ball_i-set_zone9_i)<18&&(ball_i-set_zone9_i)>-18)&&((ball_j-set_zone9_j>-18)&&(ball_j-set_zone9_j<18)))
			{
			pid1_set_f1(11,0,90);
      pid2_set_f1(11,0,90);
			set_point(set_zone9_i,set_zone9_j,ball_i,ball_j,0,0);
			}
			else
		{
			pid1_set_f1(11,0,1000);
      pid2_set_f1(11,0,1000);
			set_point(set_zone9_i,set_zone9_j,ball_i,ball_j,0,0);
		}
		
	}
		
	 /*����5����1����2��6�ٽ���9*/
		else if(function==5)
		{
			if(enter2_suc==0)
			{
			
			pid1_set_f1(22,0,850);
      pid2_set_f1(22,0,850);
			set_point(set_zone2_i,set_zone2_j,ball_i,ball_j,0,0);
			if(((ball_i-set_zone2_i)<3&&(ball_i-set_zone2_i>-3))&&((ball_j-set_zone2_j<3)&&(ball_j-set_zone2_j>-3)))
			{
			enter2_suc=1;
			}
				
			}
			
			else if(enter6_suc==0)
			{
			pid1_set_f1(18,0,800);
      pid2_set_f1(18,0,800);
			set_point(set_zone6_i,set_zone6_j,ball_i,ball_j,0,0);
				
		if(((ball_i-set_zone6_i)>-3&&(ball_i-set_zone6_i<3))&&((ball_j-set_zone6_j>-3)&&(ball_j-set_zone6_j<3)))
			{
			enter6_suc=1;
			}
			
			
			}
			
			else
			{
			pid1_set_f1(14,0,120);
      pid2_set_f1(14,0,120);
			set_point(set_zone9_i,set_zone9_j,ball_i,ball_j,0,0);
			}
			
		}
		
		/*����6��ABCD*/
		else if(function==6)
		{
			
			if(abc==1)
			{
			set_zonef_i=*(set_zone_i+select_zone-1);
			set_zonef_j=*(set_zone_j+select_zone-1);
			}
			
			
			if(abc==2)
			{
      set_zones_i=*(set_zone_i+select_zone-1);
			set_zones_j=*(set_zone_j+select_zone-1);
			}
			
			
			if(abc==3)
			{
      set_zonet_i=*(set_zone_i+select_zone-1);
			set_zonet_j=*(set_zone_j+select_zone-1);			
			}
			
			if(abc==4)
			{
				
     if(enter2_suc==0)
			{
			pid1_set_f1(22,0,850);
      pid2_set_f1(22,0,850);
			set_point(set_zonef_i,set_zonef_j,ball_i,ball_j,0,0);
			if(((ball_i-set_zonef_i)<4&&(ball_i-set_zonef_i>-4))&&((ball_j-set_zonef_j<4)&&(ball_j-set_zonef_j>-4)))
			{
			enter2_suc=1;
			}
			
			}
			else if(enter6_suc==0)
			{
			pid1_set_f1(18,0,800);
      pid2_set_f1(18,0,800);
			set_point(set_zones_i,set_zones_j,ball_i,ball_j,0,0);
				
		if(((ball_i-set_zones_i)>-4&&(ball_i-set_zones_i<4))&&((ball_j-set_zones_j>-4)&&(ball_j-set_zones_j<4)))
			{
			enter6_suc=1;
			}
			
			}
			
			else
			{
			if(((ball_i-set_zonet_i)<20&&(ball_i-set_zonet_i)>-20)&&((ball_j-set_zonet_j>-20)&&(ball_j-set_zonet_j<20)))
			{
			pid1_set_f1(14,0,120);
      pid2_set_f1(14,0,120);
			set_point(set_zonet_i,set_zonet_j,ball_i,ball_j,0,0);
			}
			else
			{
				
			pid1_set_f1(17,0,800);
      pid2_set_f1(18,0,800);
			set_point(set_zonet_i,set_zonet_j,ball_i,ball_j,0,0);
			
			}
			
			}
			
		}
			
		
		}
		
		
		/*����7����4  ����5���ܣ��ٽ���9*/
		else if(function==7)
		{
			if(fun_7_temp<22)
			{
				if(en_success==1)
				{
			
			pid1_set_f1(17,0,380);
      pid2_set_f1(17,0,382);
			set_point(set_zone5_i+29*sin(fun_7_temp),set_zone5_j-29*cos(fun_7_temp),ball_i,ball_j,0,0);
			fun_7_temp=fun_7_temp+1.57;
			en_success=0;
				}
				
				else
				{
					
			pid1_set_f1(17,0,380);
      pid2_set_f1(17,0,380);
			set_point(set_zone5_i+29*sin(fun_7_temp),set_zone5_j-29*cos(fun_7_temp),ball_i,ball_j,0,0);
			
				if(((ball_i-(set_zone5_i+29*sin(fun_7_temp)))>-10&&(ball_i-(set_zone5_i+29*sin(fun_7_temp))<10))&&((ball_j-(set_zone5_j-29*cos(fun_7_temp))>-10)&&(ball_j-(set_zone5_j-29*cos(fun_7_temp))<10)))
			{
			en_success=1;
			}
					
				}
					
			}
			
			else
			{
				
			if(((ball_i-set_zone9_i)<15&&(ball_i-set_zone9_i)>-10)&&((ball_j-set_zone9_j>-10)&&(ball_j-set_zone9_j<10)))
			{
			pid1_set_f1(13,0,100);
      pid2_set_f1(14,0,100);
			set_point(set_zone9_i,set_zone9_j,ball_i,ball_j,0,0);
			}
			else
			{
			pid1_set_f1(21,0,800);
      pid2_set_f1(21,0,800);
			set_point(set_zone9_i,set_zone9_j,ball_i,ball_j,0,0);
			}

			}
			
		}
		
		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
