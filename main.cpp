#include "bluetooth.h"
#include "utils.h"
#include "motor.h"
#include "tm4c123gh6pm.h"  
#include "cmsis_os2.h"
#include "gpio.h"
#include <string.h>
using namespace std;

void initSequence() {
	gpioService gp;
	bluetoothService bl;
	gp.gpioFInit();
	//blinkRed(3);
	bl.initService();
	bl.sendString("Ping from TIVA :)");
}

void motorControl(void *arg) {
	int dirn = 0;
	int speed = 5;
	motorService mo = motorService();
	mo.initService();
	/*
	while(1) {
		blinkRed(1);
		command = bl.readChar();
		
		if(command == 'f') {
			mo.moveForward();
		}
		else if(command == 'b') {
			mo.moveBackwards();
		}
		else if(command - '0' < 10 && command -'0' >= 0){
			speed = command - '0';
		}
		else if(command == '+'){
			speed ++;
		}
		else if(command == '-') {
			speed --;
		}
		else{
			mo.moveForward();
			bl.sendString("Command not found!!!");
		}
		
		mo.pwmSignal(10, speed);
		bl.sendString("running");
	}
	*/
	mo.pwmSignal();
}

void initThread(void *arg) {
    initSequence(); // Access using pointer
}

int main() {
	osKernelInitialize();
	int speed = 5;
	int dirn = 1;
	// Thread attributes
	osThreadAttr_t thread_attr = { .name = "Pseudo main Thread" };
	//osThreadNew(initThread, nullptr, nullptr);
	//osThreadNew(motorControl, nullptr, nullptr);
	
	osThreadAttr_t motorThreadAttr = {
    .name = "Motor Control Thread",
    .stack_size = 4096,       // Increase as necessary
    .priority = osPriorityNormal // Adjust priority if needed
};
	
osThreadId_t motorThreadId = osThreadNew(motorControl, nullptr, &motorThreadAttr);

	osKernelStart(); // Start the RTOS kernel after threads are created
}
