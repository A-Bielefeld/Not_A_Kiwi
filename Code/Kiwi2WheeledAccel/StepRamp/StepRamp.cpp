/*
 * StepRamp
 * .cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: yyunko
 */

#include"StepRamp.h"

void StepRamp::rampInitialize(int32_t steps, uint16_t speed, uint16_t accel){

	int32_t decelLimit; //steps until desired speed is reached, limit to calculate ramp type

	if (steps != 0){
		//minDelay and stepDelay are scaled by 100 to get more precision out of fixed point arithmetics to keep code fast
		this->minDelay = (uint32_t)((float)(CLOCK_SPEED)/(float)(speed)); //Calculating the minimum delay that'll be used on that ramp, that value is used to know when the cruise speed has been reached

		//this->stepDelay = (uint32_t)((1/10000.0)*CLOCK_SPEED*0.676*sqrt(2.0*10000000000/(float)(accel)));//*sqrtf(float(2/accel))); //Calculates the first inter-step delay, this value sets the acceleration rate
		this->stepDelay = (uint32_t)(CLOCK_SPEED*0.676*sqrt(2.0/(float)(accel)));//*sqrtf(float(2/accel))); //Calculates the first inter-step delay, this value sets the acceleration rate

		this->accelEnd = (int32_t)((float)(speed*speed)/(float)(accel)); //number of steps until desired speed is reached

		decelLimit =  (int32_t)(steps/2.0); //This corresponds to the step at which the accel and decel slopes intersect

		if (decelLimit <= accelEnd){ //If we cant accelerate to the cruise speed, we have to start decelerating as soon as half of the steps have been travelled
			this->decelStart = decelLimit;
		}
		else{ //Else we can just cruise until we need to decelerate
			this->decelStart = steps-accelEnd;
		}

		this->rampState = ACCEL; //Setting the statemachine to ACCEL
		this->accelCount = 0; //Resetting the accel counter that tracks the index of the interstep delay calculation
		this->stepCount = 0;
		this->rest = 0;

		cli();
		Timer1::set_prescaler(TIMER_PRESC);//Turning on the timer1 again at set prescaler value
		sei();
	}

}

uint16_t StepRamp::computeAccel(){

	switch(rampState){

	case STOP:
		Timer1::set_prescaler(TIMER1_PRESC_OFF);
		break;

	case ACCEL:

		this->stepCount++;
		this->accelCount++;

		stepDelay = (stepDelay - (2.0*stepDelay + rest)/(4.0*accelCount+1));
		rest = (uint32_t)(2.0*stepDelay + rest)%(4*accelCount+1);
		//stepDelay = (uint32_t)(stepDelay - (2*(float)stepDelay)/(4*accelCount+1));
		//rest = (uint32_t)(2*(float)stepDelay + rest)%(4*accelCount+1);

		/*if(stepCount>=decelStart){
			lastAccelDelay = stepDelay;
			accelCount = -accelCount;
			rampState = STOP;
		}*/
		/*else*/ if(stepCount<=accelEnd){
			lastAccelDelay = stepDelay;
			stepDelay = minDelay;
			rampState = RUN;
		}
		break;
	}
	/*case RUN:
		this->stepCount++;
		stepDelay = minDelay;

		if(stepCount>=decelStart){
			stepDelay = lastAccelDelay;
			accelCount = -accelCount;
			rampState = STOP;
		}
		break;
}
	/*case DECEL:
		this->stepCount++;
		this->accelCount++;

		stepDelay = (uint32_t)(stepDelay - (2*(float)stepDelay + rest)/(4*accelCount+1));
		rest = (uint32_t)(2*(float)stepDelay + rest)%(4*accelCount+1);

		if (accelCount >=0 ){
			rampState = STOP;
		}
		break;
	}*/
	return((uint16_t)(stepDelay));
}

StepRamp::StepRamp(){
	rampState = 0;
	stepDelay = 0;
	minDelay = 0;
	decelStart = 0;
	accelCount = 0;
	stepCount = 0;
	lastAccelDelay = 0;
	rest = 0;
}
