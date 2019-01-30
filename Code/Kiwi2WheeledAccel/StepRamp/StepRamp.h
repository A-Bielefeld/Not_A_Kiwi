/*
 *
 * StepRamp.h
 *
 *  Created on: Jan 24, 2019
 *      Author: yyunko
 */

#ifndef STEPRAMP_STEPRAMP_H_
#define STEPRAMP_STEPRAMP_H_

#include<avr/io.h>
#include<inttypes.h>
#include<math.h>
#include<avr/interrupt.h>
#include"../Timer1/Timer1.h"

//Speed ramp states
#define STOP  0
#define ACCEL 1
#define DECEL 2
#define RUN   3

//Timer settings
#define TIMER_PRESC TIMER1_PRESC_8
#define TIMER_PRESC_VALUE 8
#define CLOCK_SPEED (16000000/TIMER_PRESC_VALUE)

class StepRamp{

private:
	volatile uint8_t rampState; //Part of the ramp we're in
	volatile uint32_t minDelay, lastAccelDelay, stepDelay, rest, accelEnd; //Time until next step/ deceleration rate equal to the acceleration rate/ Sets the max speed
	volatile int32_t decelStart, accelCount, stepCount; //Position at which to start decelerating/ Counter for the speed ramp

public:
	//Basic Constructor
	StepRamp();

	//Sets the ramp data
	void rampInitialize(int32_t steps, uint16_t speed, uint16_t accel);

	//Computes the next step delay according to the movement logic state machine
	uint16_t computeAccel();

};

#endif /* STEPRAMP_STEPRAMP_H_ */
