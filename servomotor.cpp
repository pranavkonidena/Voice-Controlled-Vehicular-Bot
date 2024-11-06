#include "servomotor.h"
#include "TM4C123GH6PM.h"
#include "TM4C123.h"
#include "gpio.h"
#include "utils.h"


void turnLeft(int duty) {
		//gpioService gp = gpioService();
		//gp.gpioDInit();
		//gp.gpioFInit();
		for(int i = 0; i < 5; i ++){
					pwmGeneratorRight(6);
					pwmGeneratorLeft(3);
		}
}

void turnRight(int duty) {
		gpioService gp = gpioService();
		//gp.gpioDInit();
		//gp.gpioFInit();
		for(int i = 0; i < 5; i ++){
					pwmGeneratorRight(3);
					pwmGeneratorLeft(6);
		}
}


