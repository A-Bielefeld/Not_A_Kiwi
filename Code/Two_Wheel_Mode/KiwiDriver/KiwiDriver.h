/*
 * KiwiDriver.h
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#ifndef KIWIDRIVER_H_
#define KIWIDRIVER_H_

#include"../Stepper/Stepper.h"
#include"../Timer1/Timer1.h"

#define STEPS_PER_TURN 3200.0
#define WHEEL_RADIUS 3.725 //units cm
#define DIST_WHEEL_TO_WHEEL 25.0 //unis cm

#define M_PI 3.14159265358979323846 //Pi
#define DEG_TO_RAD 0.01745329238

#define TIMER_PRESC TIMER1_PRESC_1
#define TIMER_PRESC_VALUE 1
#define CLOCK_SPEED (16000000/TIMER_PRESC_VALUE)

#define MAX_SPEED_LIN 120 //units cm/s
#define MIN_SPEED_LIN 5 //units cm/s
#define MAX_SPEED_ROT 360 //units degrees/s
#define MIN_SPEED_ROT 10 //units degrees/s*/

#define PORT_STEP_R PORTD
#define PORT_DIR_R PORTD
#define PORT_EN_R PORTB
#define PIN_STEP_R 5
#define PIN_DIR_R 2
#define PIN_EN_R 3

#define PORT_STEP_L PORTD
#define PORT_DIR_L PORTD
#define PORT_EN_L PORTB
#define PIN_STEP_L 6
#define PIN_DIR_L 2
#define PIN_EN_L 3

//Usefull constants
const float wheelCircumference = 2*M_PI*WHEEL_RADIUS;
const float stepsPerCm = STEPS_PER_TURN/wheelCircumference;
const float stepsPerDegree = DEG_TO_RAD*(DIST_WHEEL_TO_WHEEL/2)*stepsPerCm;

const float ISR_period = 1/TIMER_PRESC_VALUE;

//Function that initializes timer registers
void configureISR();

//Toggles the drivers on and off
void toggle(uint8_t state);

//Issues a relative linear move command, with distance in cm, and speed in cm/s
void linearMove(float distance, float speed);

//Issues a relative rotation move command, with angle in degrees and speed in degrees/s
void rotateMove(float angle, float speed);

//Return true if the current move is done
bool moveDone();

//Blocking function, waits until kiwiReady() returns one
void waitOnMove();


#endif /* KIWIDRIVER_H_ */
