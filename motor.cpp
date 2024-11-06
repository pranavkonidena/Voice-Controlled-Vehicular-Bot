#include "motor.h"
#include "utils.h"
#include "TM4C123.h"
#include "bluetooth.h"
#include "servomotor.h"
#include "gpio.h"
using namespace std;

void motorService::pwmSignal (){
	int duty = 5;
	bluetoothService bl = bluetoothService();
	bl.initService();
	gpioService gp;
	gp.gpioFInit();
	gp.gpioDInit();
	char previousState = 'y';
	bool bluetoothState = true;
	bool firstTime = false;
  while (true) {
		//blinkRed(1);
	
		/*
		
			 bluetoothState = bl.bluetoothConnected();
				
					if(!bluetoothState ){
						if(!firstTime) blinkRed(3);
						duty = 0;
						firstTime = true;
					}
					else{
						if(firstTime){
							blinkBlue(2);
							firstTime = false;
						}
			
		*/
						//bl.sendString("debugger");
						char command = bl.readChar();
						if(command == 'x' ) command = previousState;
						if(command == 'f' ) {
						//	bl.sendString("Moving Front");
							glowGreen();
							moveForward();
							pwmGeneratorLeft(duty+2);
							pwmGeneratorRight(duty);
						}
						else if(command == 'b' ) {
						//	bl.sendString("Moving Backwards");
							glowRed();
							moveBackwards();
							pwmGeneratorLeft(duty+2);
							pwmGeneratorRight(duty);
						}
						else if(command - '0' < 10 && command -'0' >= 0){
							duty = (command - '0');
						}
						else if(command == '+'){
							duty ++;
						}
						else if(command == '-') {
							duty --;
						}
						if(command == 'l') {
								turnLeft(duty);
							continue;
						}
						else if(command == 'r'){
								turnRight(duty);
							continue;
						}
						if(command == 'f' || command == 'b') previousState = command;
		 }
	}


void motorService::initService(){
		SYSCTL->RCGC2 |= 0x20;       // Enable clock to GPIOF
    GPIOF->DIR |= 0x02;             // Set PF1 as output
    GPIOF->DEN |= 0x02;             // Enable digital function for PF1
}
