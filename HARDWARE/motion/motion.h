#ifndef _MOTION_H
#define _MOTION_H
#include "sys.h"

void i_in(int speed);

void i_de(int speed);

void j_in(int speed);

void j_de(int speed);

void set_point(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j,float l,float k);

void set_point_func1(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j);

void set_point_function2_4(int set_point_i,int set_point_j,int actuall_point_i,int actuall_point_j,float l,float k);

#endif


