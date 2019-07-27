#include "motion.h"
#include "usart.h"
#include "pid.h"

//X  PF8    Y  PF9
//		TIM_SetCompare1(TIM14,20000-2000);
//		TIM_SetCompare1(TIM13,20000-2000);
//平着的时候 设为18000
//
//13平着的时候为 18550  i
//14平着的时候为20000-1300  j
void i_in(int speed) //小球i坐标增加
{
	 speed=speed+18550;
	 if(speed>18850)
	 {speed=18850;}
   TIM_SetCompare1(TIM13,speed);
}

void i_de(int speed)
{
   speed=18550-speed;
		if(speed<18250)
	 {speed=18250;}
	
   TIM_SetCompare1(TIM13,speed);
}

void j_in(int speed)//小球j坐标增加
{
	 speed=18700-speed;
	  if(speed<18400)
	 {speed=18400;}
   TIM_SetCompare1(TIM14,speed);
}

void j_de(int speed)
{
	 speed=18700+speed;
	if(speed>19000)
	 {speed=19000;}
   TIM_SetCompare1(TIM14,speed);
}



void set_point_func1(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j)
{
	int speed_i,speed_j;
	pid1_set_f1(1,0,20);
	pid2_set_f1(1,0,20);
	speed_i=pid_position(set_point_i,actuall_point_i);
	speed_j=pid_position2(set_point_j,actuall_point_j);
	//printf("speed_i:%d speed_j:%d actuall_point_i:%d  actuall_point_j:%d \r\n",speed_i,speed_j,actuall_point_i,actuall_point_j);
	if(speed_i>0)  //设定大于实际值，实际值要增加
	{
    i_in(speed_i);
	}
	
	else if(speed_i<0)  
	{
		speed_i=-speed_i;
    i_de(speed_i);
	}
	
	 if(speed_j>0)  //设定大于实际值，实际值要增加
	{
    j_in(speed_j);
	}
	
	else if(speed_j<0)  
	{
		speed_j=-speed_j;
    j_de(speed_j);
	}
	
}

u8 two_finish=0;
void set_point_function2_4(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j,float l,float k)
{
	int speed_i,speed_j;
	float err_1=0,err_2=0;
	static int num_count=0;

	speed_i=pid_position(set_point_i,actuall_point_i);
	speed_j=pid_position2(set_point_j,actuall_point_j);
	//printf("speed_i:%d speed_j:%d actuall_point_i:%d  actuall_point_j:%d \r\n",speed_i,speed_j,actuall_point_i,actuall_point_j);
	err_1=err_return1();
	err_2=err_return2();
	if(err_1<8&err_2<8)
	{
	num_count++;
	}
	if (num_count>80)
	{
	two_finish=1;
	}
	
	if(speed_i>0)  //设定大于实际值，实际值要增加
	{
    i_in(speed_i);
	}
	
	else if(speed_i<0)  
	{
		speed_i=-speed_i;
    i_de(speed_i);
	}
	
	 if(speed_j>0)  //设定大于实际值，实际值要增加
	{
    j_in(speed_j);
	}
	
	else if(speed_j<0)  
	{
		speed_j=-speed_j;
    j_de(speed_j);
	}
	
}

void set_point(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j,float l,float k)
{
	int speed_i,speed_j;
	speed_i=pid_position(set_point_i,actuall_point_i);
	speed_j=pid_position2(set_point_j,actuall_point_j);
	//printf("speed_i:%d speed_j:%d actuall_point_i:%d  actuall_point_j:%d \r\n",speed_i,speed_j,actuall_point_i,actuall_point_j);
	
	if(speed_i>0)  //设定大于实际值，实际值要增加
	{
    i_in(speed_i);
	}
	
	else if(speed_i<0)  
	{
		speed_i=-speed_i;
    i_de(speed_i);
	}
	
	 if(speed_j>0)  //设定大于实际值，实际值要增加
	{
    j_in(speed_j);
	}
	
	else if(speed_j<0)  
	{
		speed_j=-speed_j;
    j_de(speed_j);
	}
	
}


