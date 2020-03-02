#include <stdlib.h>
#include <math.h>
#include "control.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>


#define NDEBUG
// init vehicle state
State vehicle_state = {0.0,0.0,0.0,0.0};
Control cntrl = {1,1,1,0.1,0.0,0.0,0.01};
Data data;

/*
	Clips value based on max and min
	
	@INPUTS: n: value, min: min value, max: max value

*/
static float clip(float n, float min, float max)
{
	return fmax(min,fmin(n,max));	

}

/*Dot product
*/
static float dot_prod(float* a,float* b,size_t n)
{
	float sum = 0.0;
	for (size_t i=0;i<n;i++){
		sum += a[i]*b[i];
	}
	return sum;
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
	Find shortest distance from vehicle position to path
	by calculating min hypothenuse

	returns index location of closest point in path
*/
static void short_hypo(Data* data,float fx,float fy,float* cx,float* cy,int size)
{
	float dx[size];float dy[size];

	for (int i=0;i<size;++i){
		dx[i] = fx - cx[i];
		dy[i] = fy - cy[i];		
	
	}	
	float hypo = 0.0;
	float min = 100000.0;
	int loc = 0;
	for (int i=0;i<size;++i){
		
		hypo = hypot(dx[i],dy[i]);
		
		if (hypo < min){
			min = hypo;
			loc = i;
		}	
	}

	// return struct that gives all the info
	data->loc = loc;
	data->dx = dx;
	data->dy = dy;
	
}


/*
	Calculate the next point in the path to follow
*/
static void calc_target_index(State* state,float* cx,float* cy,int size)
{
	// calculate front axle position
	float fx = (state->x) + WHEEL_BASE * cos(state->head);
	float fy = (state->y) + WHEEL_BASE * sin(state->head);
	
	// Find shortest point to travel to
	short_hypo(&data,fx,fy,cx,cy,size);

	/*
	calculate error between front axle vector & target point 
	using dot product
	neg: vectors poiting in opposite directions
	0: vectors are perpendicular
	pos: pointing in similar direction
	*/
	float front_axle_vec[2] = {-cos(state->head+PI/2),
				-sin(state->head+PI/2)};
	float vector[2] = {data.dx[data.loc],data.dy[data.loc]};
	float err_frnt_axl = dot_prod(vector,front_axle_vec,2);

	data.err_f_axle = err_frnt_axl;


}


float pid_control(float target,float current,float lat_err,float time)
{

	// pump the breaks
	if (fabs(lat_err)>cntrl.p_lat_err){
		target *= 0.5;	
	}

	cntrl.p_lat_err = fabs(lat_err);

	float time_elap = clock()/CLOCKS_PER_SEC - cntrl.p_time;
	float err = target - current;
	float err_rate = (err-cntrl.p_err);
	
	cntrl.p_err = err;
	cntrl.p_time = time;

	float d_gain = cntrl.Kd * err_rate/time_elap;
	float i_gain = cntrl.Ki * (cntrl.p_state - (err*time_elap));
	float p_gain = cntrl.Kp * (target - current);

	return d_gain + i_gain + p_gain;	 

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


/*
	Stanley steering control (kinematic)
	@INPUTS: Pointer to State of vehicle
		 path points
		 target x location

	@returns: pointer to array with steering control & target index
*/
void stanley(State* state,float* cx,float* cy,int last_trgt)
{
	// call calc_target_index to get both of these
	int new_trgt = data.loc;
	float err_front_axle = data.err_f_axle;

	if (last_trgt >= new_trgt){
		new_trgt = last_trgt;
	}

	float angle_err = atan2(cy[new_trgt]-(state->y),cx[new_trgt]
			  -(state->x));
	// Correct heading error
	float theta_e = normalize_angle(angle_err - (state->head));
	// correct cross track error
	float theta_d = atan2(K * err_front_axle,(state->v));	
	
	float delta = theta_e + theta_d;

	cntrl.delta = delta;
	data.loc = new_trgt;


}




int main()
{
	float og = 3.5;
	assert(clip(og,5,10) == 5);
	float value = 3.141593;
	assert(normalize_angle(3.0*PI) == value);


	State test = {1.0,1.0,1.0,1.0};
	printf("og state:\n%f\n%f\n%f\n%f\n",test.x,test.y,test.head,test.v);
	update(&test,29.81,10*(PI/180));
	printf("new state:\n%f\n%f\n%f\n%f\n",test.x,test.y,test.head,test.v);
	
	return 0;


}
