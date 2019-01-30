/*
 * KiwiAccel.cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: yyunko
 */


#include"KiwiAccel.h"

//Creates the robot's driver motors
Stepper motorRight(&PORT_STEP_R, &PORT_DIR_R, &PORT_EN_R, PIN_STEP_R, PIN_DIR_R, PIN_EN_R, STEPS_PER_TURN);
Stepper motorLeft(&PORT_STEP_L, &PORT_DIR_L, &PORT_EN_L, PIN_STEP_L, PIN_DIR_L, PIN_EN_L, STEPS_PER_TURN);

StepRamp rampData;

void moveKiwi(int32_t steps, uint16_t speed, uint16_t accel, bool moveType){

	if (moveType){
		motorRight.setStepsToGo(-steps);
		motorLeft.setStepsToGo(steps);
	}
	else{
		motorRight.setStepsToGo(steps);
		motorLeft.setStepsToGo(steps);
	}

	rampData.rampInitialize(steps, speed, accel);

}

void configureISR(){
	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_prescaler(TIMER1_PRESC_OFF);
	sei();
}

bool moveDone(){
	if (motorRight.done() && motorLeft.done()){
		return true;
	}
	else{
		return false;
	}
}

void waitOnMove(){
	while (!moveDone()){
	}
}

ISR (TIMER1_COMPA_vect){

	OCR1A = rampData.computeAccel();

	if (!motorLeft.done()){
		motorLeft.step();
	}
	if (!motorRight.done()){
		motorRight.step();
	}


}
