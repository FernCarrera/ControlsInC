#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
#include <math.h>
/*
	Struct defining the vehicle's state
*/

typedef struct State{
	float x;
	float y;
	float head;
	float v;
}State;

const float MAX_STEERING_ANGLE =  40*(M_PI/180);
const float DT =  0.1;
const float WHEEL_BASE = 1.9;
const float PI = 3.141593;

/*
	Updates the state of the vehicle, utilizing 
	a bicycle model

	@INPUTS: State struct, Accel [m/s^2], delta: steering angle [deg]

*/
void update(State *state,float accel,float delta);


	






#endif
