/*
 * KiwiAccel.h
 *
 *  Created on: Jan 24, 2019
 *      Author: yyunko
 */

#ifndef KIWIDRIVERV2_KIWIACCEL_H_
#define KIWIDRIVERV2_KIWIACCEL_H_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"../Stepper/Stepper.h"
#include"../StepRamp/StepRamp.h"

//Relevant robot constants
#define STEPS_PER_TURN 3200.0 //units steps
#define WHEEL_RADIUS 3.725 //units cm
#define DIST_WHEEL_TO_WHEEL 25.0 //unis cm

//Math constants
#define M_PI 3.14159265358979323846 //Pi
#define DEG_TO_RAD 0.01745329238

//Limits the robot movement
#define MAX_SPEED_LIN 120 //units cm/s
#define MIN_SPEED_LIN 5 //units cm/s
#define MAX_SPEED_ROT 360 //units degrees/s
#define MIN_SPEED_ROT 10 //units degrees/s*/

//Pin declaration for the propulsion stepper motor drivers
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

/*const float wheelCircumference = 2*M_PI*WHEEL_RADIUS;
const float stepsPerCm = STEPS_PER_TURN/wheelCircumference;
const float stepsPerDegree = DEG_TO_RAD*(DIST_WHEEL_TO_WHEEL/2)*stepsPerCm;
const float ISR_period = 1/TIMER_PRESC_VALUE;*/

//speed in steps/s, accel in steps/s², moveType is True for linear, and False for rotate.
void moveKiwi(int32_t steps, uint16_t speed, uint16_t accel, bool moveType);

//Configure the proper mode for the interrupts
void configureISR();

//Return true if the current move is done
bool moveDone();

//Blocking function, waits until moveDone() returns one
void waitOnMove();

#endif /* KIWIDRIVERV2_KIWIACCEL_H_ */
