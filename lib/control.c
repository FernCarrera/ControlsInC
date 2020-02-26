#include <stdlib.h>
#include <math.h>
#include "control.h"
#include <assert.h>

// init vehicle state
State vehicle_state = {0.0,0.0,0.0,0.0};


/*
	Updates the state of the vehicle, utilizing 
	a bicycle model

	@INPUTS: State struct, Accel [m/s^2], delta: steering angle [deg]

*/

void update(State *state,float accel,float delta)
{


}

/*
	Clips value based on max and min
	
	@INPUTS: n: value, min: min value, max: max value

*/
static float clip(float n, float min, float max)
{
	return fmax(min,fmin(n,max));	

}

int main()
{
	float og = 3.5;
	assert(clip(og,5,10) == 5);
	

}
