#include "pid.h"
#include "math.h"
#include "lcd.h"


 struct _pid_position//静态变量，每次运算后保持原来的值不变，是全局的。
       {
         float setspeed;
				 float Actualspeed;
				 float err;
				 float err_last;
				 float KP,KI,KD;
				 float p_value;
				 float i_value;
				 float d_value;
				 float dd_value;
				 float voltage;
         }pid1,pid2;
	
				 
void pid1_init(void)
{
  pid1.Actualspeed=0;
  pid1.err=0;
  pid1.err_last=0;
	pid1.p_value=0;
	pid1.i_value=0;
	pid1.d_value=0;
	pid1.dd_value=0;
	pid1.setspeed=0;
	pid1.KD=0;
	pid1.KI=0;
	pid1.KP=0;
	pid1.voltage=0;
}


void pid2_init(void)
{
	
  pid2.Actualspeed=0;
  pid2.err=0;
  pid2.err_last=0;
	pid2.p_value=0;
	pid2.i_value=0;
	pid2.d_value=0;
	pid2.dd_value=0;
	pid2.setspeed=0;
	pid2.KD=0;
	pid2.KI=0;
	pid2.KP=0;
	pid2.voltage=0;
}


void pid1_set_f1(float kp,float ki,float kd)
{
	
  pid1.KD=kd;
	pid1.KI=ki;
	pid1.KP=kp;
}


void pid2_set_f1(float kp,float ki,float kd)
{
	
	pid2.KD=kd;
	pid2.KI=ki;
	pid2.KP=kp;
	
}

float err_return1(void)
{
	if(pid1.err<0)
		pid1.err=-pid1.err;
	return pid1.err;
}

float err_return2(void)
{
		if(pid2.err<0)
		pid2.err=-pid2.err;
	return pid2.err;
}




float pid_position(float sspeed,float spead)
{
	
  pid1.setspeed=sspeed;
	pid1.Actualspeed=spead;
	pid1.err=pid1.setspeed-pid1.Actualspeed;
  
	pid1.p_value=pid1.err;
	pid1.i_value+=pid1.err;	
	pid1.d_value=pid1.err-pid1.err_last;
	pid1.dd_value=pid1.err-pid1.err_last;
	pid1.voltage = pid1.KP*pid1.p_value+pid1.KI*pid1.i_value+pid1.KD*pid1.d_value;
	pid1.err_last = pid1.err;
	pid1.Actualspeed=pid1.voltage;
	return pid1.Actualspeed;
	
}

//区域1到区域5最佳
//	{	
//	pid2.KD=100;
//	pid2.KP=10;
//	}
	
float pid_position2(float sspeed,float spead)
{
	
  pid2.setspeed=sspeed;
	pid2.Actualspeed=spead;
	pid2.err=pid2.setspeed-pid2.Actualspeed;
	
	
	pid2.p_value=pid2.err;
	pid2.i_value+=pid2.err;	
	pid2.d_value=pid2.err-pid2.err_last;
	pid2.voltage = pid2.KP*pid2.p_value+pid2.KI*pid2.i_value+pid2.KD*pid2.d_value;
	pid2.err_last = pid2.err;
	pid2.Actualspeed=pid2.voltage;
	return pid2.Actualspeed;
	
}


