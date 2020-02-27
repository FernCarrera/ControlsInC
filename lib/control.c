#include <stdlib.h>
#include <math.h>
#include "control.h"
#include <assert.h>
#include <stdio.h>
// init vehicle state
State vehicle_state = {0.0,0.0,0.0,0.0};

/*
	Clips value based on max and min
	
	@INPUTS: n: value, min: min value, max: max value

*/
static float clip(float n, float min, float max)
{
	return fmax(min,fmin(n,max));	

}


/*
	keeps angle within -2pi and 2pi
*/
static float normalize_angle(float angle)
{
	while (angle > PI){
		angle -= 2.0 * PI;
	}
	while (angle < -PI){
		angle += 2.0 * PI;
	}
	return angle;
}

/*
	Updates the state of the vehicle, utilizing 
	a bicycle model

	@INPUTS: State struct, Accel [m/s^2], delta: steering angle [deg]

*/
void update(State* state,float accel,float delta)
{
	delta = clip(delta,-MAX_STEERING_ANGLE,MAX_STEERING_ANGLE);
	
	state->x += state->v * cos(state->head)*DT;
	state->y += state->v * sin(state->head)*DT;
	state->head += state->v / WHEEL_BASE * tan(delta) * DT;
	state->head = normalize_angle(state->head);
}


int main()
{
	float og = 3.5;
	assert(clip(og,5,10) == 5);
	float value = 3.141593;
	assert(normalize_angle(3.0*PI) == value);

}
