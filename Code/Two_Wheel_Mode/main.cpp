/*
 * main.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#include<avr/io.h>
#include"KiwiDriver/KiwiDriver.h"

int main(){
	configureISR();

	while(1){
		linearMove(10.0, 10);
		waitOnMove();
		rotateMove(90.0, 70.0);
		waitOnMove();
	}
	return 0;
}



