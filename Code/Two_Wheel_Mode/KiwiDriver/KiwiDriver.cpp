/*
 * KiwiDriver.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include"KiwiDriver.h"
#include"../Stepper/Stepper.h"

//Creates the robot's driver motors
Stepper motorRight(&PORT_STEP_R, &PORT_DIR_R, &PORT_EN_R, PIN_STEP_R, PIN_DIR_R, PIN_EN_R, STEPS_PER_TURN);
Stepper motorLeft(&PORT_STEP_L, &PORT_DIR_L, &PORT_EN_L, PIN_STEP_L, PIN_DIR_L, PIN_EN_L, STEPS_PER_TURN);

void configureISR(){
	Timer1::set_mode(TIMER1_MODE_CTC);
	Timer1::set_prescaler(TIMER1_PRESC_1);
	sei();
}

void toggle(uint8_t state){
	motorRight.toggle(state);
	motorLeft.toggle(state);
}

void linearMove(float distance, float speed){
	if (speed<MIN_SPEED_LIN) {speed = MIN_SPEED_LIN;}
	else if (speed>MAX_SPEED_LIN) {speed = MAX_SPEED_LIN;}

	motorRight.move((int32_t)(-distance*stepsPerCm));
	motorLeft.move((int32_t)(distance*stepsPerCm));

	speed = (speed*stepsPerCm); //Converting to steps/s

	cli();
	Timer1::set_OCR1A((uint16_t)(CLOCK_SPEED/speed));
	sei();
}

void rotateMove(float angle, float speed){
	if (speed<MIN_SPEED_ROT) {speed = MIN_SPEED_ROT;}
	else if (speed>MAX_SPEED_ROT) {speed = MAX_SPEED_ROT;}

	motorRight.move((int32_t)(angle*stepsPerDegree));
	motorLeft.move((int32_t)(angle*stepsPerDegree));

	speed = (speed*stepsPerDegree); //Converting to steps/s

	cli();
	Timer1::set_OCR1A((uint16_t)(CLOCK_SPEED/speed));
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
	if (!motorLeft.done()){
		motorLeft.step();
	}
	if (!motorRight.done()){
		motorRight.step();
	}
}
