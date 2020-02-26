#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
/*
	Struct defining the vehicle's state
*/

typedef struct State{
	float x;
	float y;
	float head;
	float v;
}State;


/*
	Updates the state of the vehicle, utilizing 
	a bicycle model

	@INPUTS: State struct, Accel [m/s^2], delta: steering angle [deg]

*/
void update(State *state,float accel,float delta);


/*
	Clips value based on max and min
	
	@INPUTS: n: value, min: min value, max: max value

*/
static float clip(float n, float min, float max);

#endif
