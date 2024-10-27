#include "servomotor.h"
#include "TM4C123GH6PM.h"
#include "TM4C123.h"
#include "gpio.h"
#include "utils.h"

void servoGenerator(int direction) {
    // -1 means left
		// 1 means right
    // Turn ON the GPIO pin (PF3)
    GPIOD->DATA |= (1 << 6);             // Set PF2 high (turn ON PD3 for servo control)
		int controlTime = 700 + direction*200;
    for(int i = 0; i < controlTime; i++) systick1Us();   // Delay for ON time (duty cycle)

    // Turn OFF the GPIO pin (PF3)
    GPIOD->DATA &= ~(1 << 6);            // Set PF2 low (turn OFF PD3)
    for(int i = 0; i < 20000 - controlTime; i++) systick1Us();  // Delay for OFF time to complete 20 ms cycle
}

void turnLeft() {
		gpioService gp = gpioService();
		gp.gpioDInit();
	// calling once turns it 10 degrees left
    servoGenerator(-1); // Pulse to move servo by 10° left
		for(int i = 0;i<10;i++) systick1Ms();
}

void turnRight() {
		gpioService gp = gpioService();
		gp.gpioDInit();
	// calling it once turns it 10 degrees right
    servoGenerator(1); // Pulse to move servo by 10° right
		for(int i = 0;i<10;i++) systick1Ms();
}


