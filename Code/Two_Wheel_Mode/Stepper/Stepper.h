/*
 * Stepper.h
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#ifndef STEPPER_H_
#define STEPPER_H_

class Stepper{
private:
	volatile uint8_t* _portStep, *_portDir, *_portEn; //Port Register Pointers
	uint8_t _pinStep, _pinDir, _pinEn; //Number of the pin on that port (from 0 to 7)

	volatile int32_t _stepsToGo, _currentPosition; //Number of steps left to move, and current position in steps (negative or positive values)
	int16_t _stepsPerRotation; //Delay between each step for that motor, steps per full rotation


public:
	//Constructor for the stepper class, using a driver interface with step, port and enable pins, specify ports and pins on those ports (0 to 7)
	Stepper(volatile uint8_t* portStep, volatile uint8_t* portDir, volatile uint8_t* portEn, uint8_t pinStep, uint8_t pinDir, uint8_t pinEn, int16_t stepsPerRotation);

	//Steps the motor once into the required direction
	void step(uint8_t dir);
	void step();

	//Switches the stepper on or off (on is 1, off is 0, the functions assumes that enable is an active low)
	void toggle(uint8_t state);

	//Sets the distance to travel, in steps
	void move(int32_t distance);

	//Return true if the motor has finished moving
	bool done();


};

#endif /* STEPPER_H_ */
