#ifndef __PID_H
#define __PID_H	 
#include "sys.h"


void pid1_init(void);
void pid2_init(void);
float pid_position(float sspeed,float spead);
float pid_position2(float sspeed,float spead);
void pid1_set_f1(float kp,float ki,float kd);
void pid2_set_f1(float kp,float ki,float kd);
float err_return1(void);
float err_return2(void);

#endif


