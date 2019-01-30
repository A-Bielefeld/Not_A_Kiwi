/*
 * main.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: yyunko
 */

#include"KiwiDriverV2/KiwiAccel.h"

int main(){

	configureISR();
	moveKiwi(30000, 10000, 1000, true);

	while(1){
	}
	return 0;
}


