#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
#include <math.h>
/*
	Struct defining the vehicle's state
*/


// struct return for hypothenuse function
typedef struct Data{
	int loc;
	float err_f_axle;
	float* dx;
	float* dy;
}Data; 

typedef struct State{
	float x;
	float y;
	float head;
	float v;
}State;

typedef struct Control{
	float Kp;
	float Ki;
	float Kd;
	float delta;
	float p_lat_err;
	float p_state;
	float p_err;
	float p_time;

}Control;

const float MAX_STEERING_ANGLE =  40*(M_PI/180);
const float DT =  0.1;
const float WHEEL_BASE = 1.9;
const float PI = 3.141593;
const float K = 0.5; // Stanley control gain
/*
	Updates the state of the vehicle, utilizing 
	a bicycle model

	@INPUTS: State struct, Accel [m/s^2], delta: steering angle [deg]

*/
void update(State *state,float accel,float delta);

void stanley(State* state,float* cx,float* cy,int last_trgt);
	
float pid_control(Control* cntrl,float target,float current,float lat_err,float time);

void print_state(State* state);

void calc_target_index(State* state,Data* data,float* cx,float* cy,int size);

void short_hypo(Data* data,float fx,float fy,float* cx,float* cy,int size);


#endif
