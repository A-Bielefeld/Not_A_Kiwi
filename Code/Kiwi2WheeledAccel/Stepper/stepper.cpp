/*
 * stepper.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#include<avr/io.h>
#include"Stepper.h"

Stepper::Stepper(volatile uint8_t* portStep, volatile uint8_t* portDir, volatile uint8_t* portEn, uint8_t pinStep, uint8_t pinDir, uint8_t pinEn, int16_t stepsPerRotation){
		this->_portStep = portStep;
		this->_pinStep = pinStep;

		this->_portDir = portDir;
		this->_pinDir = pinDir;

		this->_portEn = portEn;
		this->_pinEn = pinEn;

		this->_stepsToGo = 0;
		this->_currentPosition = 0;		//Steppers start at the 0 position
		this->_stepsPerRotation = stepsPerRotation;

		*(_portStep - 1) |= (1 << _pinStep);
		*(_portDir - 1) |= (1 << _pinDir);
		*(_portEn - 1) |= (1 << _pinEn);	//Declaring the pins as outputs, DDRx address is one below PORTx.
}

void Stepper::step(uint8_t dir){
	if (dir == 0) {		//Rotate it backwards
		*_portDir |= (1 << _pinDir);	//Set the direction pin, then activate the stepping pin and deactivate both immediately
		*_portStep |= (1 << _pinStep);
		*_portStep &= ~(1 << _pinStep);
		_stepsToGo++;	//One step backwards was done; increase the amount of steps to do and decrease the total amount
		_currentPosition--;
	}
	else {		//Rotate it forward
		*_portDir &= ~(1 << _pinDir);
		*_portStep |= (1 << _pinStep);
		*_portStep &= ~(1 << _pinStep);
		_stepsToGo--;	//Decrease the steps to do and increase total amount of steps done.
		_currentPosition++;
	}
}

void Stepper::step(){
	if (_stepsToGo < 0){
		step(0);
	}
	else{
		step(1);
	}
}

void Stepper::toggle(uint8_t state){
	if (state == 0){
		*_portEn |= (1 << _pinEn);	//Assumes Enable is an active low
	}
	else {
		*_portEn &= ~(1 << _pinEn);
	}
}

void Stepper::setStepsToGo(int32_t distance){
	_stepsToGo = distance;
}

bool Stepper::done(){
	if (_stepsToGo == 0){
		return true;
	}
	else{
		return false;
	}
}
